// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>

class UESPIELEPROTOTYPBLUE_API PythonInterface
{
public:
	PythonInterface();
	~PythonInterface();

	void CreatePipeServer();
	bool RunPipeServer();
	BOOL StopPipeServer();

private:
	HANDLE _pipeHandle = INVALID_HANDLE_VALUE;
	char _buffer[1024];
};
