// Fill out your copyright notice in the Description page of Project Settings.


#include "VillagerNamedPipeAsync.h"

VillagerNamedPipeAsync::VillagerNamedPipeAsync(FString pipeName, NeuralNetworkData* nnData, bool* isNnDataUpdated)
{
	_pipeName = pipeName;
	_nnData = nnData;
	_isNnDataUpdated = isNnDataUpdated;
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
	pyInterface->CreatePipeServer(_pipeName, _nnData, _isNnDataUpdated);
	pyInterface->RunPipeServer();

	return 1;
}

void VillagerNamedPipeAsync::Exit()
{
	
}

void VillagerNamedPipeAsync::Stop()
{
}
