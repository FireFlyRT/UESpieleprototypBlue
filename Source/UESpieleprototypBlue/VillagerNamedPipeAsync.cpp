// Fill out your copyright notice in the Description page of Project Settings.


#include "VillagerNamedPipeAsync.h"

VillagerNamedPipeAsync::VillagerNamedPipeAsync()
{
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
	pyInterface->CreatePipeServer();
	pyInterface->RunPipeServer();

	/*
	* PythonInterface:
	* 
	* Connect to Main Pipe
	* 
	* Wait for Connection to Interface Program over VillagerID as PipeName
	* 
	* Send SensorData
	* Receive NeuralNetworkData
	*/

	return 1;
}

void VillagerNamedPipeAsync::Exit()
{
	
}

void VillagerNamedPipeAsync::Stop()
{
}
