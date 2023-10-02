import argparse
import collections

import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
import time

from tensorboardX import SummaryWriter

DEFAULT_ENV_NAME = "PongNoFrameskip-v4"
MEAN_REWARD_BOUND = 19.5

GAMMA = 0.99
BATCH_SIZE = 32
REPLAY_SIZE = 10000
REPLAY_START_SIZE = 10000
LEARNING_RATE = 0.001
SYNC_TARGET_FRAMES = 1000

EPSILON_DECAY_LAST_FRAME = 1000000
EPSILON_START = 1.0
EPSILON_FINAL = 0.02

Experience = collections.namedtuple('Experience', field_names = ['state', 'action', 'reward', 'done', 'new_state'])

class DQN(nn.Module):
    def __init__(self, input_shape, n_actions):
        super(DQN, self).__init__()

        self.conv = nn.Sequential(
            nn.Conv2d(input_shape[0], 32, kernel_size = 8, stride = 4),
            nn.ReLU(),
            nn.Conv2d(32, 64, kernel_size = 4, stride = 2),
            nn.ReLU(),
            nn.Conv2d(64, 64, kernel_size = 3, stride = 1),
            nn.ReLU()
            )

        convOutSize = self.GetConvOut(input_shape)
        self.fc = nn.Sequential(
            nn.Linear(convOutSize, 512),
            nn.ReLU(),
            nn.Linear(512, n_actions)
        )

    def GetConvOut(self, shape):
        tz = torch.zeros(1, *shape)
        out = self.conv(tz)
        return int(np.prod(out.size()))
    
    def forward(self, x):
        convOut = self.conv(x).view(x.size()[0], -1)
        return self.fc(convOut)
    
class Agent:
    def __init__(self, env, exp_buffer):
        self.env = env
        self.exp_buffer = exp_buffer
        self.Reset()

    def Reset(self):
        # self.state = self.env.reset() uncomment if new env has Reset()
        self.total_reward = 0.0

    def PlayStep(self, net, epsilon = 0.0, device = "GPU"):
        done_reward = None

        if np.random.random() < epsilon:
            action = self.env.action_space.sample()
        else:
            state_a = np.array([self.state], copy = False)
            state_v = torch.tensor(state_a).to(device)
            q_vals_v = net(state_v)
            _, act_v = torch.max(q_vals_v, dim = 1)
            action = int(act_v.item())

            new_state, reward, is_done, _ = self.env.step(action) # Step on Environment
            self.total_reward += reward
            new_state = new_state

            exp = Experience(self.state, action, reward, is_done, new_state)
            self.exp_buffer.append(exp)
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
    
class ExperienceBuffer:
    def __init__(self, capacity):
        self.buffer = collections.deque(maxlen = capacity)

    def __len__(self):
        return len(self.buffer)
    
    def append(self, experience):
        self.buffer.append(experience)

    def sample(self, batch_size):
        indces = np.random.choice(len(self.buffer), batch_size, replace = False)
        states, actions, rewards, dones, next_states = zip(*[self.buffer[idx] for idx in indces])
        return np.array(states), np.array(actions), np.array(rewards, dtype = np.float32), np.array(dones, dtype = np.uint8), np.array(next_states)

class Program:
    def __init__(self):
        parser = argparse.ArgumentParser()
        parser.add_argument("--cuda", default = False, action = "store_true", help = "Enable cuda")
        parser.add_argument("--env", default = DEFAULT_ENV_NAME, help = "Environment")
        parser.add_argument("--reward", type = float, default = MEAN_REWARD_BOUND, help = "Mean Reward")
        args = parser.parse_args()
        device = torch.device("cuda" if args.cuda else "cpu")

        env = args.env # Replace with env from C++
        #net = DQN(env.observation_space.shape, env.action_space.n).to(device) # Add ObservationSpace and ActionSpace to Env
        self.net = DQN([1, 128, 128], 8).to(device)
        #target_net = DQN(env.observation_space.shape, env.action_space.n).to(device)
        self.target_net = DQN([1, 128, 128], 8).to(device)

        self.writer  = SummaryWriter(comment = "-" + args.env)
        print(self.net)

        buffer = ExperienceBuffer(REPLAY_SIZE)
        self.agent = Agent(env, buffer)
        self.epsilon = EPSILON_START
        self.optimizer = optim.Adam(self.net.parameters(), lr = LEARNING_RATE)
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

if __name__ == "__main__":
    program = Program()
    #program.Start()