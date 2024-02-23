// Fill out your copyright notice in the Description page of Project Settings.


#include "VillagerNamedPipeAsync.h"

VillagerNamedPipeAsync::VillagerNamedPipeAsync(FString* villagerName, NeuralNetworkData* nnData, SensorData* sensorData, StatData* statData, RewardData* rewardData)
{
	_villagerName = villagerName;
	_nnData = nnData;
	_sensorData = sensorData;
	_statData = statData;
	_rewardData = rewardData;
}

VillagerNamedPipeAsync::~VillagerNamedPipeAsync()
{
}

bool VillagerNamedPipeAsync::Init()
{
	return true;
}

uint32 VillagerNamedPipeAsync::Run()
{
	PythonInterface* pyInterface = new PythonInterface();
	pyInterface->CreatePipeServer(_villagerName, _nnData, _sensorData, _statData, _rewardData);
	pyInterface->RunPipeServer(_villagerName);

	return 1;
}

void VillagerNamedPipeAsync::Exit()
{
	
}

void VillagerNamedPipeAsync::Stop()
{
}
