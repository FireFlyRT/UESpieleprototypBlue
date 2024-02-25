// Fill out your copyright notice in the Description page of Project Settings.

#include "PythonInterface.h"
#include "CrypticHelper.h"

#define BUFFER_SIZE 512

PythonInterface::PythonInterface()
{
	
}

PythonInterface::~PythonInterface()
{
}

void PythonInterface::CreatePipeServer(FString* villagerName, NeuralNetworkData* nnData, SensorData* sensorData, StatData* statData, RewardData* rewardData)
{
	_nnData = nnData;
	_sensorData = sensorData;
	_statData = statData;
	_rewardData = rewardData;

	FString projectFilePath = FPaths::GetProjectFilePath();
	FString projectPath = FPaths::GetPath(projectFilePath);
	std::string jsonVillagerFile = TCHAR_TO_UTF8(*projectPath);
	std::string jsonVillagerPath = std::string("/PythonInterface/JSONData/");

	std::string villagerBuffer = TCHAR_TO_UTF8(**villagerName);
	jsonVillagerFile.append(jsonVillagerPath);
	jsonVillagerFile.append(villagerBuffer);
	_jsonVillagerPath = std::string(jsonVillagerFile);

	std::string jsonNnDataFile = TCHAR_TO_UTF8(*projectPath);
	std::string jsonNnDataPath = std::string("/PythonInterface/JSONData/");

	std::string NnDataBuffer = TCHAR_TO_UTF8(**villagerName);
	jsonNnDataFile.append(jsonNnDataPath);
	jsonNnDataFile.append(NnDataBuffer);
	_jsonNnDataPath = jsonNnDataFile;

	// Send VillagerID to extern PyInterface
	std::string send("New ");
	send.append(villagerBuffer);
	jsonVillagerFile.append(".json");
	CrypticHelper::WriteJsonToFile(send, jsonVillagerFile, true);
	UE_LOG(LogTemp, Warning, TEXT("Pipe Interface running"));
}

/// <summary>
/// Starts the named Pipe Server
/// </summary>
bool PythonInterface::RunPipeServer(FString* villagerPipeName)
{
	//	TODO (Major): Workflow UnrealInterface (multiline)
	//	On Run:
	//		- Connect to MainPipe
	//		- Send VillagerID to MainPipe
	//	While (true):
	//		- Get SensorData, StatData, RewardData (via Pointer)
	//		- Encrypt Data with CrypticHelper (Data to String)
	//		- Send string to extern PyInterface
	//	
	//	On Data Receive:
	//		- Decrypt Data with CrypticHelper (String to NNData)
	//		- Send nnData to Enhanced Character (via Pointer)
	//	

	int jsonCount = 0;
	bool emptyFileExisted = false;

	FString projectFilePath = FPaths::GetProjectFilePath();
	FString projectPath = FPaths::GetPath(projectFilePath);
	std::string jsonEmptyFile = TCHAR_TO_UTF8(*projectPath);
	std::string jsonEmptyPath = std::string("/PythonInterface/JSONData/");
	jsonEmptyFile.append(jsonEmptyPath);
	jsonEmptyFile.append("Empty.json");

	while (true)
	{
		// Check if ExternInterface is ready
		if (!emptyFileExisted)
		{
			if (FPaths::FileExists(FString(jsonEmptyFile.c_str())))
				emptyFileExisted = true;
			continue;
		}
			
		if (FPaths::FileExists(FString(jsonEmptyFile.c_str())))
			continue;

		// Write data to json
		// SensorData, StatData, RewardData
		std::string data = CrypticHelper::EncryptValue(_sensorData, _statData, _rewardData); // returns json
		if (data.empty())
			// Fallback
			//data = std::string("{'SensorDat': ['2016','0','0','0','0','0','0','101','0','0','0','0','0'],'StatData': ['0','0','0','0','0','0','0','101','0','0','0','0'],'RewardData': ['0']}");
			continue;
		
		//UE_LOG(LogTemp, Warning, TEXT("Write Data: %s"), data.c_str());
		std::string filePath = std::string(_jsonVillagerPath);
		filePath.append(".json");
		CrypticHelper::WriteJsonToFile(data, filePath, true);

		// Read data from json Action, Movement, Rotation
		std::string jsonNnDataFile = std::string(_jsonNnDataPath);
		jsonNnDataFile.append(std::string("_"));
		jsonNnDataFile.append(std::to_string(jsonCount));
		jsonNnDataFile.append(".json");
		FString fp = FString(jsonNnDataFile.c_str());
		//UE_LOG(LogTemp, Error, TEXT("nnData from: %s"), *fp);
		while (!FPaths::FileExists(fp));
		//jsonCount += 1;
		// Data per Pointer to EnhancedCharacterController
		_nnData = CrypticHelper::DecryptValue(new FString(jsonNnDataFile.c_str()));
		if (_nnData != nullptr)
		{
			_nnData->IsUpdated = true;
		}

		// TEST BREAK
		// TODO (Major): Loop verhindert beenden des Programms!!!
		//UE_LOG(LogTemp, Error, TEXT("TEST break"));
		//break;
	}
	//UE_LOG(LogTemp, Error, TEXT("return"));
	
	return true;
}
