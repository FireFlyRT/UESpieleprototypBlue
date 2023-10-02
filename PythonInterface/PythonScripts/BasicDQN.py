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
        self.state = self.env.reset()
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

            new_state, reward, is_done, _ = self.env.step(action)
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

if __name__ == "__main__":

    parser = argparse.ArgumentParser()
    parser.add_argument("--cuda", default = False, action = "store_true", help = "Enable cuda")
    parser.add_argument("--env", default = DEFAULT_ENV_NAME, help = "Environment")
    parser.add_argument("--reward", type = float, default = MEAN_REWARD_BOUND, help = "Mean Reward")
    args = parser.parse_args()
    device = torch.device("cuda" if args.cuda else "cpu")

    env = args.env # Replace with env from C++
    #net = DQN(env.observation_space.shape, env.action_space.n).to(device) # Add ObservationSpace and ActionSpace to Env
    net = DQN([1, 128, 128], 8).to(device)
    #target_net = DQN(env.observation_space.shape, env.action_space.n).to(device)
    target_net = DQN([1, 128, 128], 8).to(device)

    writer  = SummaryWriter(comment = "-" + args.env)
    print(net)

    buffer = ExperienceBuffer(REPLAY_SIZE)
    agent = Agent(env, buffer)
    epsilon = EPSILON_START
    optimizer = optim.Adam(net.parameters(), lr = LEARNING_RATE)
    total_rewards = []
    frame_idx = 0
    ts_frame = 0
    ts = time.time()
    best_mean_reward = None

    while True:
        frame_idx += 1
        epsilon = max(EPSILON_FINAL, EPSILON_START - frame_idx / EPSILON_DECAY_LAST_FRAME)
        reward = agent.PlayStep(net, epsilon, device = device)

        if reward is not None:
            total_rewards.append(reward)
            speed = (frame_idx - ts_frame) / (time.time() - ts)
            ts_frame = frame_idx
            ts = time.time()
            mean_reward = np.mean(total_rewards[-100:])

            writer.add_scalar("epsilon", epsilon, frame_idx)
            writer.add_scalar("speed", speed, frame_idx)
            writer.add_scalar("reward_100", mean_reward, frame_idx)
            writer.add_scalar("reward", reward, frame_idx)

            if best_mean_reward is None or best_mean_reward < mean_reward:
                torch.save(net.state_dict(), args.env + "-best.dat")
                if best_mean_reward is not None:
                    print("Best mean Reward updatet")
                
                if mean_reward > args.reward:
                    print("Solved in " + frame_idx + " frames")
                    break

            if len(buffer) < REPLAY_START_SIZE:
                continue

        if frame_idx % SYNC_TARGET_FRAMES == 0:
            target_net.load_state_dict(net.state_dict())

        optimizer.zero_grad()
        batch = buffer.sample(BATCH_SIZE)
        loss_t = agent.CalcLoss(batch, net, target_net, device = device)
        loss_t.backward()
        optimizer.step()