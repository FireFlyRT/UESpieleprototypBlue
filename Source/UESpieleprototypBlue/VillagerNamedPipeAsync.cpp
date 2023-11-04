// Fill out your copyright notice in the Description page of Project Settings.


#include "VillagerNamedPipeAsync.h"

VillagerNamedPipeAsync::VillagerNamedPipeAsync(FString pipeName)
{
	_pipeName = pipeName;
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
	pyInterface->CreatePipeServer(_pipeName);
	pyInterface->RunPipeServer();

	return 1;
}

void VillagerNamedPipeAsync::Exit()
{
	
}

void VillagerNamedPipeAsync::Stop()
{
}
