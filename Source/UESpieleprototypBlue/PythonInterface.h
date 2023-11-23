// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NeuralNetworkData.h"
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>

class UESPIELEPROTOTYPBLUE_API PythonInterface
{
public:
	PythonInterface();
	~PythonInterface();

	void CreatePipeServer(FString pipeName, NeuralNetworkData* nnData, bool* isNnDataUpdated);
	bool RunPipeServer();
	BOOL StopPipeServer();

private:
	HANDLE _pipeHandle = INVALID_HANDLE_VALUE;
	TCHAR* _buffer;
	NeuralNetworkData* _nnData;
	bool* _isNnDataUpdated;
};
