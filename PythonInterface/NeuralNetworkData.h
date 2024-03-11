#pragma once
#include "string"
#include "fstream"
#include "nlohmann/json.hpp"

class NeuralNetworkData
{
public:
	float MovementX;
	float MovementY;
	float RotationZ;
	int Action;

public:
	NeuralNetworkData();
	void GetNeuralNetworkDataFromJSON(std::string jsonPath, std::string fileID, std::string fileCount);

};

