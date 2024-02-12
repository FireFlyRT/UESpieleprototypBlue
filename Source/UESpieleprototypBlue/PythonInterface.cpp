// Fill out your copyright notice in the Description page of Project Settings.

#include "PythonInterface.h"
#include <filesystem>
#include "CrypticHelper.h"

#define BUFFER_SIZE 512

PythonInterface::PythonInterface()
{
	
}

PythonInterface::~PythonInterface()
{
}

// TODO (MAJOR): Pipe needs to be closed when Application closes
void PythonInterface::CreatePipeServer(FString* villagerName, NeuralNetworkData* nnData, SensorData* sensorData)
{
	_nnData = nnData;
	_sensorData = sensorData;

	std::string jsonVillagerPath = "/JSONData/";
	FILE* villagerFile = nullptr;
	char* villagerBuffer = new char(***villagerName);
	jsonVillagerPath.append(villagerBuffer);
	jsonVillagerPath.append(".json");
	_jsonVillagerPath = jsonVillagerPath.c_str();

	// Send VillagerID to extern PyInterface
	int count = 0;
	fopen_s(&villagerFile, _jsonVillagerPath.c_str(), "w");
	fwrite(villagerBuffer, sizeof(villagerBuffer) * sizeof(char), count, villagerFile);
	fclose(villagerFile);
}

/// <summary>
/// Starts the named Pipe Server
/// </summary>
bool PythonInterface::RunPipeServer(FString* villagerPipeName)
{
	UE_LOG(LogTemp, Warning, TEXT("Pipe Interface running"));

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

	while (true)
	{
		// Write data to namedPipe
		// SensorData, StatData, RewardData
		FILE* villagerFile = nullptr;
		std::string data1 = CrypticHelper::EncryptValue(/*_sensorData*/);
		const char* data = "00,000,100,050,030,024,189,043,042,1.0000000;0.3821341;1.0421621,010205,00,000,100,050,030,024,189,043,042,1.0000000;0.3821341;1.0421621,1.2458"; // TEMP TEST
		int count = 0;
		fopen_s(&villagerFile, _jsonVillagerPath.c_str(), "w");
		fwrite(data, sizeof(data) * sizeof(char), count, villagerFile);
		fclose(villagerFile);

		// Read data from namedPipe
		// Action, Movement, Rotation
		while (!std::filesystem::exists(_jsonVillagerPath));
		int count = 0;
		char buffer[255];
		fopen_s(&villagerFile, _jsonVillagerPath.c_str(), "r");
		fread(buffer, sizeof(buffer) * sizeof(char), count, villagerFile);
		fclose(villagerFile);

		//UE_LOG(LogTemp, Warning, TEXT("Last Error: %s"), GetLastError());
		
		// Data per Pointer to EnhancedCharacterController
		_nnData = CrypticHelper::DecryptValue(std::string(buffer));
		if (_nnData->Null != NULL)
		{
			_nnData->IsUpdated = true;
		}

		// TEST BREAK
		// TODO (Major): Loop verhindert beenden des Programms!!!
		UE_LOG(LogTemp, Error, TEXT("break"));
		break;
	}
	UE_LOG(LogTemp, Error, TEXT("return"));
	
	return true;
}
