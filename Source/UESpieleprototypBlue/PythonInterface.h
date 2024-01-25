// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NeuralNetworkData.h"
#include "SensorData.h"
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>

class UESPIELEPROTOTYPBLUE_API PythonInterface
{
public:
	PythonInterface();
	~PythonInterface();

	FString* CreatePipeServer(FString* pipeName, NeuralNetworkData* nnData, SensorData* sensorData);
	bool RunPipeServer(FString* villagerPipeName);
	BOOL StopPipeServer();

private:
	HANDLE* _pipeHandle = new HANDLE(INVALID_HANDLE_VALUE);
	TCHAR* _buffer;
	NeuralNetworkData* _nnData;
	SensorData* _sensorData;
	FString* _villagerPipeName;
};
