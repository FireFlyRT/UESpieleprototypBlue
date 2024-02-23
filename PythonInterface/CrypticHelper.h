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
	static bool DeserializeFromJSON(std::string jsonPath, SensorData* sensorData, StatData* statData, RewardData* rewardData);
	static std::string EncryptValue(NeuralNetworkData* data);
	static std::string SerializeToJSON(NeuralNetworkData* data);
	static bool WriteFileWithJSON(std::string jsonData, std::string filePath);
	static std::string SymbolNumberAdjustment(int value, int symbolNum);
};

