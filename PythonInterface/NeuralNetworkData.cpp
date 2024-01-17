#include "NeuralNetworkData.h"
#include <iostream>

NeuralNetworkData::NeuralNetworkData()
{
	MovementX = 0;
	MovementY = 0;
	RotationZ = 0;
	RotationY = 0;
	Action = 0;
}

void NeuralNetworkData::GetNeuralNetworkDataFromJSON(std::string jsonPath, std::string fileID, std::string fileCount)
{
	std::string fileName = jsonPath;
	fileName.append("/");
	fileName.append(fileID);
	fileName.append("_");
	fileName.append(fileCount);
	fileName.append(".json");
	std::ifstream file(fileName);
	nlohmann::json jsonData = nlohmann::json::parse(file);

	std::string data[5];

	int i = 0;
	for (nlohmann::json::iterator jd = jsonData.begin(); jd != jsonData.end(); jd++)
	{
		std::cout << jd.key() << ", " << jd.value() << std::endl; // LOG
		data[i] = jd.value();
		i++;
	}

	Action = std::stof(data[0]);	   
	MovementX = std::stof(data[1]);	   
	MovementY = std::stof(data[2]);	   
	RotationZ = std::stof(data[3]);	   
	RotationY = std::stof(data[4]);	   
}
