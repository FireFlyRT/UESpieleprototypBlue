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

// TODO (MAJOR): Pipe needs to be closed when Application closes
FString* PythonInterface::CreatePipeServer(FString* pipeName, NeuralNetworkData* nnData, SensorData* sensorData)
{
	_nnData = nnData;
	_sensorData = sensorData;

	TCHAR* namePrefix = TEXT("\\\\.\\pipe\\");
	char name[256] = { 0 };
	//TCHAR* name = namePrefix + *pipeName->GetCharArray().GetData();
	snprintf(name, sizeof(namePrefix) + pipeName->GetAllocatedSize(), "\\\\.\\pipe\\%ls", **pipeName);
	_villagerPipeName = new FString(name);
	FString vPipeName = FString(*_villagerPipeName);

	_pipeHandle = new HANDLE(CreateNamedPipe(
		(LPCWSTR)*vPipeName,
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		BUFFER_SIZE,
		BUFFER_SIZE,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL));
	UE_LOG(LogTemp, Warning, TEXT("Villager Server Created! Name: %ls"), *vPipeName);

	if (_pipeHandle == INVALID_HANDLE_VALUE)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pipe invalid after Creation"));
	}

	return _villagerPipeName;
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

	DWORD read;
	DWORD written;
	FString vPipeName = FString(*villagerPipeName);

	while (true)
	{
		UE_LOG(LogTemp, Error, TEXT("while true"));
		if (*_pipeHandle == INVALID_HANDLE_VALUE)
		{
			_pipeHandle = new HANDLE(CreateNamedPipe(
				(LPCWSTR)*vPipeName,
				PIPE_ACCESS_DUPLEX,
				PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
				PIPE_UNLIMITED_INSTANCES,
				BUFFER_SIZE,
				BUFFER_SIZE,
				NMPWAIT_USE_DEFAULT_WAIT,
				NULL));
			UE_LOG(LogTemp, Warning, TEXT("Pipe recreated! Name: %ls"), *vPipeName);
		}
		UE_LOG(LogTemp, Error, TEXT("pipe handle recreation Name: %ls"), *vPipeName);

		if (*_pipeHandle == INVALID_HANDLE_VALUE)
		{
			UE_LOG(LogTemp, Warning, TEXT("Pipe invalid before Connecting! Name: %ls"), *vPipeName);
			return true;
		}
		UE_LOG(LogTemp, Error, TEXT("pipe handle check Name: %ls"), *vPipeName);

		if (ConnectNamedPipe(*_pipeHandle, NULL) == FALSE) // if noone connects to the pipe, stop and try again
		{
			UE_LOG(LogTemp, Error, TEXT("Client disconnected!"));
			StopPipeServer();
			continue;
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("Connection esteblished with client"));
		UE_LOG(LogTemp, Error, TEXT("connection check"));
		
		// Write data to namedPipe
		// SensorData, StatData, RewardData
		while (true)
		{
			std::string data1 = CrypticHelper::EncryptValue(/*_sensorData*/);
			const char* data = "00,000,100,050,030,024,189,043,042,1.0000000;0.3821341;1.0421621,010205,00,000,100,050,030,024,189,043,042,1.0000000;0.3821341;1.0421621,1.2458"; // TEMP TEST
			bool success = WriteFile(*_pipeHandle, data, sizeof(data), &written, NULL);
			UE_LOG(LogTemp, Warning, TEXT("Writing Data...!!! -> %s"), written);
			if (!success)
			{
				UE_LOG(LogTemp, Error, TEXT("Writing Data failed"));
				break;
			}
		}

		// Read data from namedPipe
		// Action, ...
		while (true)
		{
			bool success = ReadFile(*_pipeHandle, _buffer, BUFFER_SIZE * sizeof(TCHAR), &read, NULL);
			UE_LOG(LogTemp, Warning, TEXT("Reading Data..."));
			if (!success)
			{
				//UE_LOG(LogTemp, Error, TEXT("Reading Data failed"));
				break;
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("DATA WAS READED!!! -> %s"), read);

		//UE_LOG(LogTemp, Warning, TEXT("Last Error: %s"), GetLastError());
		
		// Data per Pointer to EnhancedCharacterController
		_nnData = CrypticHelper::DecryptValue(std::to_string(read));
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

/// <summary>
/// Stop the running named Pipe Server
/// </summary>
/// <returns>true: If server was closed | false: Closing failed</returns>
BOOL PythonInterface::StopPipeServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Server Stopped"));
	FlushFileBuffers(*_pipeHandle);
	DisconnectNamedPipe(*_pipeHandle);
	return CloseHandle(*_pipeHandle);
}
