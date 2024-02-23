// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NeuralNetworkData.h"
#include "SensorData.h"
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <strsafe.h>
#include "StatData.h"
#include "RewardData.h"

class UESPIELEPROTOTYPBLUE_API PythonInterface
{
public:
	PythonInterface();
	~PythonInterface();

	void CreatePipeServer(FString* pipeName, NeuralNetworkData* nnData, SensorData* sensorData, StatData* statData, RewardData* rewardData);
	bool RunPipeServer(FString* villagerPipeName);

private:
	std::string _jsonVillagerPath;
	std::string _jsonNnDataPath;
	NeuralNetworkData* _nnData;
	SensorData* _sensorData;
	StatData* _statData;
	RewardData* _rewardData;
};
