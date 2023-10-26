#pragma once
#include <string>
#include "SensorData.h"
#include "NeuralNetworkData.h"

class CrypticHelper
{
public:
	static SensorData* DecryptValue(std::string value);
	static std::string EncryptValue(NeuralNetworkData* data);
};

