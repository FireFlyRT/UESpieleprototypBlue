#pragma once
#include <string>
#include "SensorData.h"
#include "NeuralNetworkData.h"
#include "StatData.h"
#include "RewardData.h"

class CrypticHelper
{
public:
	static bool DecryptValue(std::string value, SensorData* sensorData, StatData* statData, RewardData* rewardData);
	static std::string EncryptValue(NeuralNetworkData* data);
};

