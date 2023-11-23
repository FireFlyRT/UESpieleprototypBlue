// Fill out your copyright notice in the Description page of Project Settings.

#include "PythonInterface.h"
#include "CrypticHelper.h"

#define BUFFER_SIZE 512

// TODO (MAJOR): Copy .dll's in Build Folder!!!
PythonInterface::PythonInterface()
{
	// Open new Python Interface Program
	//system("..\\UESpieleprototypBlue\\x64\\Release\\PythonInterface.exe");
	//system("..\\UESpieleprototypBlue\\x64\\Debug\\PythonInterface.exe");
	//UE_LOG(LogTemp, Warning, TEXT("PythonInterfaceProgram open"));
}

PythonInterface::~PythonInterface()
{
}

// TODO (MAJOR): Pipe needs to be closed when Application closes
void PythonInterface::CreatePipeServer(FString pipeName, NeuralNetworkData* nnData, bool* isNnDataUpdated)
{
	_nnData = nnData;
	_isNnDataUpdated = isNnDataUpdated;

	TCHAR* namePrefix = TEXT("\\\\.\\pipe\\");
	TCHAR* name = namePrefix + *pipeName.GetCharArray().GetData();
	_pipeHandle = CreateNamedPipe(
		(LPCWSTR)name, // Get Name from MainPipe
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, // | FILE_FLAG_FIRST_PIPE_INSTANCE is not needed but forces CreateNamedPipe(..) to fail if the pipe already exists
		PIPE_UNLIMITED_INSTANCES,
		BUFFER_SIZE,
		BUFFER_SIZE,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL);
	UE_LOG(LogTemp, Warning, TEXT("Server Created!!!"));
}

/// <summary>
/// Starts the named Pipe Server
/// </summary>
bool PythonInterface::RunPipeServer()
{
	DWORD read;
	DWORD written;

	while (1)
	{
		if (_pipeHandle == INVALID_HANDLE_VALUE)
		{
			UE_LOG(LogTemp, Warning, TEXT("Pipe invalid before Connecting"));
			return true;
		}

		if (ConnectNamedPipe(_pipeHandle, NULL) == FALSE) // if noone connects to the pipe, stop and try again
		{
			UE_LOG(LogTemp, Warning, TEXT("Client disconnected!"));
			StopPipeServer();
			return false;
		}

		UE_LOG(LogTemp, Warning, TEXT("Connection esteblished with client"));
		// Write data to namedPipe
		// SensorData, StatData, RewardData
		while (true)
		{
			//char* data = GET_DATA_FROM_UNREAL();
			const char* data = "00,000,100,050,030,024,189,043,042,1.0000000;0.3821341;1.0421621,010205,00,000,100,050,030,024,189,043,042,1.0000000;0.3821341;1.0421621,1.2458"; // TEMP TEST
			bool success = WriteFile(_pipeHandle, data, sizeof(data), &written, NULL);
			UE_LOG(LogTemp, Warning, TEXT("Writing Data..."));
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
			bool success = ReadFile(_pipeHandle, _buffer, BUFFER_SIZE * sizeof(TCHAR), &read, NULL);
			UE_LOG(LogTemp, Warning, TEXT("Reading Data..."));
			if (!success)
			{
				UE_LOG(LogTemp, Error, TEXT("Reading Data failed"));
				break;
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("DATA WAS READED!!! -> %s"), read);

		//UE_LOG(LogTemp, Warning, TEXT("Last Error: %s"), GetLastError());

		std::wstring w = _buffer;
		std::string data = std::string(w.begin(), w.end());
		*_nnData = CrypticHelper::DecryptValue(data);
		if (_nnData->Null != 0)
		{
			*_isNnDataUpdated = true;
		}
		// Data per Pointer to EnhancedCharacterController

		return false;
	}
	
}

/// <summary>
/// Stop the running named Pipe Server
/// </summary>
/// <returns>true: If server was closed | false: Closing failed</returns>
BOOL PythonInterface::StopPipeServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Server Stoped"));
	FlushFileBuffers(_pipeHandle);
	DisconnectNamedPipe(_pipeHandle);
	return CloseHandle(_pipeHandle);
}
