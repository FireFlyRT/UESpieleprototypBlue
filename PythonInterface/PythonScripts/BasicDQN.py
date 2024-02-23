import argparse
import collections
import json

import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
import time

from tensorboardX import SummaryWriter

DEFAULT_ENV_NAME = "Ahricination"
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
            # 25 Inputs (13 Sensor / 12 Stat)
            # Change to LinearLayer!
            nn.Linear(input_shape[0], 25),
            nn.ReLU(),
            nn.Linear(25, 50),
            nn.ReLU(),
            nn.Linear(50, 96),
            nn.ReLU(),
            nn.Linear(96, 512),
            nn.ReLU(),
            nn.Linear(512, n_actions)
            )
    
    def forward(self, x):
        return self.conv(x)
    
class Agent:
    def __init__(self, env, exp_buffer):
        self.env = env
        self.exp_buffer = exp_buffer
        self.state = np.array([])
        self.Reset()

    # Reset only for Debug purpuses!
    def Reset(self):
        #self.state = self.env.reset()
        self.total_reward = 0.0

    def PlayStep(self, net, epsilon = 0.0, device = "GPU"):
        if np.random.random() < epsilon:
            action = self.env.actionSpace.sample()
            # Random Move and Rotation
        else:
            state_a = np.array([self.state], copy = False)
            state_v = torch.tensor(state_a).to(device)
            q_vals_nnData_v = net(state_v) # Get more than one return
            _, act_v = torch.max(q_vals_nnData_v.action, dim = 1)
            action = int(act_v.item())

        self.env.step(action) # Step on Environment
        # Result of the Step will be returned later by Unreal
        
    def ExperienceStep(self, action, new_state, reward, is_done):
        done_reward = None
        self.total_reward += reward

        exp = Experience(self.state, action, reward, is_done, new_state)
        self.exp_buffer.append(exp)
        self.state = new_state
        if is_done:
            done_reward = self.total_reward
            # Reset only for Debug purpuses!
            #self.Reset()

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
    def __init__(self, villagerID):
        parser = argparse.ArgumentParser()
        parser.add_argument("--cuda", default = False, action = "store_true", help = "Enable cuda")
        parser.add_argument("--env", default = DEFAULT_ENV_NAME, help = "Environment")
        parser.add_argument("--reward", type = float, default = MEAN_REWARD_BOUND, help = "Mean Reward")
        self.args = parser.parse_args()
        self.device = torch.device("cuda" if self.args.cuda else "cpu")
        self.epsilon = 0
        actionSpace = ActionSpace()
        observationSpace = np.array([])
        self.env = Environment(villagerID, actionSpace, observationSpace)

        self.writer  = SummaryWriter(comment = "-" + self.args.env)
        self.buffer = ExperienceBuffer(REPLAY_SIZE)
        self.agent = Agent(self.env, self.buffer)
        self.epsilon = EPSILON_START
        self.total_rewards = []
        self.frame_idx = 0
        self.ts_frame = 0
        self.ts = time.time()
        self.best_mean_reward = None
        self.net = None
        self.target_net = None
        self.optimizer = None

    def LateInit(self):
        self.net = DQN(self.env.observationSpace.shape, self.env.actionSpace.actions.__len__()).to(self.device)
        self.target_net = DQN(self.env.observationSpace.shape, self.env.actionSpace.actions.__len__()).to(self.device)
        self.optimizer = optim.Adam(self.net.parameters(), lr = LEARNING_RATE)
        # DEBUG
        #self.net = DQN([1, 128, 128], 8).to(self.device)
        #self.target_net = DQN([1, 128, 128], 8).to(self.device)

    def Step(self):
        self.frame_idx += 1
        epsilon = max(EPSILON_FINAL, EPSILON_START - self.frame_idx / EPSILON_DECAY_LAST_FRAME)
        self.agent.PlayStep(self.net, epsilon, device = self.device)
        self.epsilon = epsilon

    def OnGetReward(self, reward):
        if reward is not None:
            self.total_rewards.append(reward)
            if time.time() - self.ts > 0:
                speed = (self.frame_idx - self.ts_frame) / (time.time() - self.ts)
            else:
                speed = (self.frame_idx - self.ts_frame)
            self.ts_frame = self.frame_idx
            self.ts = time.time()
            mean_reward = np.mean(self.total_rewards[-100:])

            self.writer.add_scalar("epsilon", self.epsilon, self.frame_idx)
            self.writer.add_scalar("speed", speed, self.frame_idx)
            self.writer.add_scalar("reward_100", mean_reward, self.frame_idx)
            self.writer.add_scalar("reward", reward, self.frame_idx)

            if self.best_mean_reward is None or self.best_mean_reward < mean_reward:
                torch.save(self.net.state_dict(), self.args.env + "-best.dat")
                if self.best_mean_reward is not None:
                    print("Best mean Reward updatet")
                
                if mean_reward > self.args.reward:
                    #print("Solved in " + str(self.frame_idx) + " frames")
                    return

            if len(self.buffer) < REPLAY_START_SIZE:
                return

        if self.frame_idx % SYNC_TARGET_FRAMES == 0:
            self.target_net.load_state_dict(self.net.state_dict())

        # later?
        self.optimizer.zero_grad()
        batch = self.buffer.sample(BATCH_SIZE)
        loss_t = self.agent.CalcLoss(batch, self.net, self.target_net, device = self.device)
        loss_t.backward()
        self.optimizer.step()

class Environment:
    def __init__(self, villagerID, actionSpace, observationSpace):
        self.jsonCount = 0
        self.villagerID = villagerID # is int
        self.actionSpace = actionSpace # is ActionSpace
        self.observationSpace = observationSpace # is Array with Sensor-/StatData == state

    def SetObservationSpace(self, observationSpace):
        self.observationSpace = observationSpace

    def SetObservationSpace(self, sensorData, statData):
        data = np.array([])

        for s in range(0, sensorData.__len__()):
            data.__add__(sensorData[s])

        for s in range(0, statData.__len__()):
            data.__add__(statData[s])

        self.observationSpace = data
        return data

    def reset():
        # return state
        pass

    def step(self, action):
        # do stuff

        # Get Data From NN

        # Save Data in JSON file
        pyJson = PyToJSON()
        data = NNData(60, 0, 20, 30, action) # Get Move and Rotation too
        pyJson.convertToJSON(str(self.villagerID), str(self.jsonCount), data)
        #self.jsonCount += 1

class ActionSpace:
    def __init__(self): # 0 = Nothing, 1 = Punch, 2 = Jump
        self.actions = [0, 1, 2] #, 3, 4] #, 5, 6, 7, 8, 9]

    def __len__(self):
        return self.actions.__len__()
    
    def sample(self):
        return self.actions[np.random.randint(0, self.actions.__len__())-1]

class RewardData:
    def __init__(self, reward):
        self.reward = reward
        # isdone

class SensorData:
    def __init__(self, classCategory, tribeId, livePoints, stamina, strength, age,
                 height, hunger, thurst, positionX, positionY, positionZ, distance):
        self.classCategory = classCategory
        self.tribeId = tribeId
        self.livePoints = livePoints
        self.stamina = stamina
        self.strength = strength
        self.age = age
        self.height = height
        self.hunger = hunger
        self.thurst = thurst
        self.positionX = positionX
        self.positionY = positionY
        self.positionZ = positionZ
        self.distance = distance

    def GetData(self):
        data = [self.classCategory, self.tribeId, self.tribeId, self.livePoints, self.stamina, self.strength, self.age, self.height, self.hunger, self.thurst, self.positionX, self.positionY, self.positionZ, self.distance]
        return data

class StatData:
    def __init__(self, classCategory, tribeId, livePoints, stamina, strength, age,
                 height, hunger, thurst, positionX, positionY, positionZ):
        self. classCategory = classCategory
        self.tribeId = tribeId
        self.livePoints = livePoints
        self.stamina = stamina
        self.strength = strength
        self.age = age
        self.height = height
        self.hunger = hunger
        self.thurst = thurst
        self.positionX = positionX
        self.positionY = positionY
        self.positionZ = positionZ

    def GetData(self):
        data = [self.classCategory, self.tribeId, self.tribeId, self.livePoints, self.stamina, self.strength, self.age, self.height, self.hunger, self.thurst, self.positionX, self.positionY, self.positionZ]
        return data

class NNData:
    def __init__(self, moveX, moveY, rotX, rotY, action):
        self.moveX = moveX
        self.moveY = moveY
        self.rotX = rotX
        self.rotY = rotY
        self.action = action

class PyToJSON:
    def convertToJSON(self, fileID: str, fileCount: str, nnData: NNData):
        data = {
            "moveX": str(nnData.moveX),
            "moveY": str(nnData.moveY),
            "rotX": str(nnData.rotX),
            "rotY": str(nnData.rotY),
            "action": str(nnData.action)
        }

        j = json.dumps(data)
        fileName = fileID + "_" + fileCount + ".json"
        file = open("JSONData/" + fileName, "w")
        file.write(j)
        file.close()

# DEBUG
#if (__name__ == "__main__"):
#prog = Program()