import argparse
import collections
import random
import operator

import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
import time
import math
import torch.multiprocessing as mp

from tensorboardX import SummaryWriter
from torch.autograd import Variable

DEFAULT_ENV_NAME = "Ahricination"
MEAN_REWARD_BOUND = 19.5

GAMMA = 0.99
BATCH_SIZE = 32
REPLAY_SIZE = 10000
REPLAY_START_SIZE = 10000
UPDATE_NN_EVERY = 1
UPDATE_MEM_EVERY = 20
UPDATE_MEM_PAR_EVERY = 3000
EXPERIENCES_PER_SAMPLING = math.ceil(BATCH_SIZE * UPDATE_MEM_EVERY / UPDATE_NN_EVERY)
LEARNING_RATE = 0.001
SYNC_TARGET_FRAMES = 1000

EPSILON_DECAY_LAST_FRAME = 1000000
EPSILON_START = 1.0
EPSILON_FINAL = 0.02

USE_A3C = True
DEVICE = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")

class DQN(nn.Module):
    def __init__(self, input_shape, n_actions):
        super(DQN, self).__init__()
        self.n_actions = n_actions

        self.conv1 = nn.Conv2d(input_shape[0], 32, kernel_size = 8, stride = 4)
        self.conv2 = nn.Conv2d(32, 64, kernel_size = 4, stride = 2)
        self.conv3 = nn.Conv2d(64, 64, kernel_size = 3, stride = 1)

        self.fc1_adv = nn.Linear(7*7*64, 512)
        self.fc1_val = nn.Linear(7*7*64, 512)

        self.fc2_adv = nn.Linear(512, n_actions)
        self.fc2_val = nn.Linear(512, 1)

        self.relu = nn.ReLU()
    
    def forward(self, x):
        x = self.relu(self.conv1(x))
        x = self.relu(self.conv2(x))
        x = self.relu(self.conv3(x))
        x = x.view(x.size(0), -1)

        adv = self.relu(self.fc1_adv(x))
        val = self.relu(self.fc1_val(x))

        adv = self.fc2_adv(adv)
        val = self.fc2_val(val).expand(x.size(0), self.n_actions)

        x = val + adv - adv.mean(1).unsqueeze(1).expand(x.size(0), self.n_actions)
        return x
    
    def save(self, path, step, optimizer):
        torch.save({
            'step':step, #episode step
            'state_dict': self.state_dict(),
            'optimizer': optimizer.state_dict()
        }, path)

    def load(self, checkpoint_path, optimizer=None):
        checkpoint = torch.load(checkpoint_path)
        step = checkpoint['step'] #episode step
        self.load_state_dict(checkpoint['state_dict'])
        if optimizer is not None:
            optimizer.load_state_dict(checkpoint['optimizer'])
        
        return step
    
class Agent:
    def __init__(self, env, seed, compute_weights = False):
        self.env = env
        self.seed = random.seed(seed)
        self.compute_weights = compute_weights
        self.exp_buffer = ExperienceBuffer(env.action_space.n, REPLAY_SIZE, BATCH_SIZE, EXPERIENCES_PER_SAMPLING, seed, compute_weights)

        self.time_step_nn_update = 0
        self.time_step_mem_update = 0
        self.time_step_mem_par_update = 0

        self.Reset()

    def Reset(self):
        # self.state = self.env.reset() uncomment if new env has Reset()
        self.total_reward = 0.0

    def OnSleep(self):
        # Train here!
        pass

    def TrainLocalNetwork(self, local_net, optimizer, loss):
        local_net.train()
        
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

    def PlayStep(self, local_net, epsilon = 0.0, device = "GPU"):
        done_reward = None

        if np.random.random() < epsilon:
            action = self.env.action_space.sample()
        else:
            state_a = np.array([self.state], copy = False)
            state_v = torch.tensor(state_a).to(device)
            q_vals_v = local_net(state_v)
            _, act_v = torch.max(q_vals_v, dim = 1)
            action = int(act_v.item())

            new_state, reward, is_done, _ = self.env.step(action) # Step on Environment
            self.total_reward += reward
            new_state = new_state

            self.exp_buffer.append(self.state, action, reward, new_state, is_done)

            self.time_step_nn_update = (self.time_step_nn_update + 1) % UPDATE_NN_EVERY
            self.time_step_mem_update = (self.time_step_mem_update + 1) % UPDATE_MEM_EVERY
            self.time_step_mem_par_update = (self.time_step_mem_par_update + 1) % UPDATE_MEM_PAR_EVERY
            if self.time_step_mem_par_update == 0:
                self.exp_buffer.update_parameters()
            if self.time_step_nn_update == 0:
                if self.exp_buffer.experience_count > EXPERIENCES_PER_SAMPLING:
                    sampling = self.exp_buffer.sample()
                    # Learning is not relevant here and will be moved to a different location to wait for sleep event
                    #self.learn(sampling, GAMMA)
            if self.time_step_mem_update == 0:
                self.exp_buffer.update_memory_sampling()

            self.state = new_state
            if is_done:
                done_reward = self.total_reward
                self.Reset()

            return done_reward
        
    def CalcLoss(batch, net, target_net, device = "GPU"):
        states, actions, rewards, dones, next_states = batch
        states_v = torch.tensor(states).to(device)
        next_states_v = torch.tensor(next_states).to(device)
        actions_v = torch.tensor(actions).to(device)
        rewards_v = torch.tensor(rewards).to(device)
        done_mask = torch.ByteTensor(dones).to(device)
        stateActionValues = net(states_v).gather(1, actions_v.unsqueeze(-1).squeeze(-1))

        next_state_values = target_net(next_states_v).max(1)[0]
        next_state_values[done_mask] = 0.0
        next_state_values = next_state_values.detach()
        expected_state_action_values = next_state_values * GAMMA + rewards_v

        return nn.MSELoss()(stateActionValues, expected_state_action_values)
    
    # def Learn(): | Needed?
    
class ExperienceBuffer:
    def __init__(self, action_size, experiences_per_sampling, seed, compute_weights):
        self.action_size = action_size
        self.experiences_per_sampling = experiences_per_sampling
        self.compute_weights = compute_weights
        
        self.alpha = 0.5
        self.alpha_decay_rate = 0.99
        self.beta = 0.5
        self.beta_growth_rate = 1.001
        self.seed = random.seed(seed)
        self.experience_count = 0

        self.experience = collections.namedtuple("Experience",
            field_names = ["state", "action", "reward", "next_state", "done"])
        self.data = collections.namedtuple("Data",
            field_names = ["priority", "probability", "weight", "index"])
        
        indexes = []
        datas = []

        for i in range(REPLAY_SIZE):
            indexes.append(i)
            data = self.data(0, 0, 0, i)
            datas.append(data)

        self.memory = { key: self.experience for key in indexes }
        self.memory_data = { key: data for key, data in zip(indexes, datas) }
        self.sample_batches = []
        self.current_batch = 0
        self.priorities_sum_alpha = 0
        self.priorities_max = 1
        self.weights_max = 1

    def __len__(self):
        return len(self.memory)

    def update_prorities(self, loss, indices):
        for ls, index in zip(loss, indices):
            priority = min(self.experience_count, REPLAY_SIZE)

            updated_priority = ls[0]
            if updated_priority > self.priorities_max:
                self.priorities_max = updated_priority
            
            if self.compute_weights:
                updated_weight = ((priority * updated_priority)**(-self.beta)) / self.weights_max
                if updated_weight > self.weights_max:
                    self.weights_max = updated_weight
            else:
                updated_weight = 1

            old_priority = self.memory_data[index].priority
            self.priorities_sum_alpha += updated_priority**self.alpha - old_priority**self.alpha
            updated_probability = ls[0]**self.alpha / self.priorities_sum_alpha
            data = self.data(updated_priority, updated_probability, updated_weight, index)
            self.memory_data[index] = data

    def update_memory_sampling(self):
        self.current_batch = 0
        values = list(self.memory_data.values())
        random_values = random.choice(self.memory_data,
                                      [data.probability for data in values],
                                      k = self.experiences_per_sampling)
        self.sample_batches = [random_values[i:i + BATCH_SIZE]
                               for i in range(0, len(random_values), BATCH_SIZE)]
        
    def update_parameters(self):
        self.alpha *= self.alpha_decay_rate
        self.beta *= self.beta_growth_rate
        if self.beta > 1:
            self.beta = 1
        priority = min(self.experience_count, REPLAY_SIZE)
        self.priorities_sum_alpha = 0
        sum_prob_before = 0
        for element in self.memory_data.values():
            sum_prob_before += element.probability
            self.priorities_sum_alpha += element.priority**self.alpha
        sum_prob_after = 0
        for element in self.memory_data.values():
            probability = element.priority**self.alpha / self.priorities_sum_alpha
            sum_prob_after += probability
            weight = 1
            if self.compute_weights:
                weight = ((priority * element.probability)**(-self.beta)) / self.weights_max
            data = self.data(element.priority, probability, weight, element.index)
            self.memory_data[element.index] = data
        # Debug
        print("sum_prob before", sum_prob_before)
        print("sum_prob after : ", sum_prob_after)
    
    def append(self, state, action, reward, next_state, done):
        self.experience_count += 1
        index = self.experience_count % REPLAY_SIZE

        if self.experience_count > REPLAY_SIZE:
            data = self.memory_data[index]
            self.priorities_sum_alpha -= data.priority**self.alpha
            if data.priority == self.priorities_max:
                self.memory_data[index].priority = 0
                self.priorities_max = max(self.memory_data.items(), key = operator.itemgetter(1).priority)
            if self.compute_weights:
                if data.weight == self.weights_max:
                    self.memory_data[index].weight = 0
                    self.weights_max = max(self.memory_data.item(), key = operator.itemgetter(2).weight)

        priority = self.priorities_max
        weight = self.weights_max
        self.priorities_sum_alpha += priority**self.alpha
        probability = priority**self.alpha / self.priorities_sum_alpha
        exp = self.experience(state, action, reward, next_state, done)
        self.memory[index] = exp
        data = self.data(priority, probability, weight, index)
        self.memory_data[index] = data

    def sample(self):
        sample_batch = self.sample_batches[self.current_batch]
        self.current_batch += 1
        experiences = []
        weights = []
        indices = []

        for data in sample_batch:
            experiences.append(self.memory.get(data.index))
            weights.append(data.weight)
            indices.append(data.index)

        states = torch.from_numpy(
            np.vstack([exp.state for exp in experiences if exp is not None])).float().to(DEVICE)
        actions = torch.from_numpy(
            np.vstack([exp.action for exp in experiences if exp is not None])).long().to(DEVICE)
        rewards = torch.from_numpy(
            np.vstack([exp.reward for exp in experiences if exp is not None])).float().to(DEVICE)
        next_states = torch.from_numpy(
            np.vstack([exp.next_state for exp in experiences if exp is not None])).float().to(DEVICE)
        dones = torch.from_numpy(
            np.vstack([exp.done for exp in experiences if exp is not None])).astype(np.uint8).float().to(DEVICE)
        
        return (states, actions, rewards, next_states, dones, weights, indices)

class Program:
    def __init__(self):
        parser = argparse.ArgumentParser()
        parser.add_argument("--cuda", default = False, action = "store_true", help = "Enable cuda")
        parser.add_argument("--env", default = DEFAULT_ENV_NAME, help = "Environment")
        parser.add_argument("--reward", type = float, default = MEAN_REWARD_BOUND, help = "Mean Reward")
        self.args = parser.parse_args()
        self.device = torch.device("cuda" if self.args.cuda else "cpu")
        # def SetEnv()?

        env = self.args.env # Replace with env from C++
        #net = DQN(env.observation_space.shape, env.action_space.n).to(device) # Add ObservationSpace and ActionSpace to Env
        self.net = DQN([1, 128, 128], 8).to(self.device)
        #target_net = DQN(env.observation_space.shape, env.action_space.n).to(device)
        self.target_net = DQN([1, 128, 128], 8).to(self.device)
        
        if USE_A3C:
            self.net.share_memory()
            self.target_net.share_memory()

        self.writer  = SummaryWriter(comment = "-" + self.args.env)
        print(self.net)

        buffer = ExperienceBuffer(REPLAY_SIZE)
        self.agent = Agent(env, buffer)
        self.epsilon = EPSILON_START
        self.optimizer = optim.Adam(self.net.parameters(), lr = LEARNING_RATE)
        if USE_A3C:
            for group in self.optimizer.param_groups:
                for param in group['params']:
                    state = self.state[param]
                    state['step'].share_memory()
                    state['exp_avg'].share_memory()
                    state['exp_avg_sq'].share_memory()

        self.total_rewards = []
        self.frame_idx = 0
        self.ts_frame = 0
        self.ts = time.time()
        self.best_mean_reward = None

    def Start(self):
        while True:
            self.frame_idx += 1
            epsilon = max(EPSILON_FINAL, EPSILON_START - self.frame_idx / EPSILON_DECAY_LAST_FRAME)
            reward = self.agent.PlayStep(self.net, epsilon, device = self.device)

            if reward is not None:
                self.total_rewards.append(reward)
                speed = (self.frame_idx - ts_frame) / (time.time() - ts)
                ts_frame = self.frame_idx
                ts = time.time()
                mean_reward = np.mean(self.total_rewards[-100:])

                self.writer.add_scalar("epsilon", epsilon, self.frame_idx)
                self.writer.add_scalar("speed", speed, self.frame_idx)
                self.writer.add_scalar("reward_100", mean_reward, self.frame_idx)
                self.writer.add_scalar("reward", reward, self.frame_idx)

                if self.best_mean_reward is None or self.best_mean_reward < mean_reward:
                    torch.save(self.net.state_dict(), self.args.env + "-best.dat")
                    if self.best_mean_reward is not None:
                        print("Best mean Reward updatet")
                    
                    if mean_reward > self.args.reward:
                        print("Solved in " + self.frame_idx + " frames")
                        break

                if len(self.buffer) < REPLAY_START_SIZE:
                    continue

            if self.frame_idx % SYNC_TARGET_FRAMES == 0:
                self.target_net.load_state_dict(self.net.state_dict())

            self.optimizer.zero_grad()
            batch = self.buffer.sample(BATCH_SIZE)
            loss_t = self.agent.CalcLoss(batch, self.net, self.target_net, device = self.device)
            loss_t.backward()
            self.optimizer.step()

    def OnSleep(self):
        processes = []
        counter = mp.Value('i', 0)
        lock = mp.Lock()

        for rank in range(0, self.args.num_processes):
            # Learn-Function will be started. Make sure all arguments match the function args
            process = mp.Process(self.agent.Learn, (rank, self.args, self.net, self.target_net, lock, counter, self.optimizer))
            process.start()
            processes.append(process)
