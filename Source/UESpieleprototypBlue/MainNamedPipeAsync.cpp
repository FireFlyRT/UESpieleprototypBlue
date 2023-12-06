// Fill out your copyright notice in the Description page of Project Settings.


#include "MainNamedPipeAsync.h"
#include <iostream>
#include "VillagerNamedPipeAsync.h"

#define BUFFER_SIZE 512

MainNamedPipeAsync::MainNamedPipeAsync()
{
}

MainNamedPipeAsync::~MainNamedPipeAsync()
{
}

bool MainNamedPipeAsync::Init()
{
	return true;
}
uint32 MainNamedPipeAsync::Run()
{
	_pipeHandle = CreateNamedPipe(
		(LPCWSTR)*_mainPipeName,
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT | FILE_FLAG_FIRST_PIPE_INSTANCE, // is not needed but forces CreateNamedPipe(..) to fail if the pipe already exists
		PIPE_UNLIMITED_INSTANCES,
		BUFFER_SIZE,
		BUFFER_SIZE,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL);

	for (;;)
	{
		if (_pipeHandle == INVALID_HANDLE_VALUE)
		{
			UE_LOG(LogTemp, Warning, TEXT("MainPipe creation failed!!!"));
			return -1;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("MainPipe-Server Created! Name: %s"), *_mainPipeName);
		}

		if (ConnectNamedPipe(_pipeHandle, NULL) != FALSE)
		{
			UE_LOG(LogTemp, Warning, TEXT("Connection esteblished with a client"));

			// From VillagerPipe:
			// TODO (Major): In Queue (Or one Client at a Time), 

			//Start extern PyInterface
			// TODO (MAJOR): Copy .dll's in Build Folder!!!
			//system("..\\UESpieleprototypBlue\\x64\\Release\\PythonInterface.exe");
			//system("..\\UESpieleprototypBlue\\x64\\Debug\\PythonInterface.exe");
			UE_LOG(LogTemp, Warning, TEXT("PythonInterfaceProgram open"));

			// Get VillagerID from VillagerPipe
			wchar_t* villagerID = new wchar_t;
			while (1)
			{
				DWORD read;

				bool success = ReadFile(_pipeHandle, _buffer, BUFFER_SIZE * sizeof(TCHAR), &read, NULL);
				UE_LOG(LogTemp, Warning, TEXT("Reading Data..."));
				if (!success)
				{
					UE_LOG(LogTemp, Error, TEXT("Reading Data failed"));
					break;
				}
				villagerID = (wchar_t*)read;
			}
			UE_LOG(LogTemp, Warning, TEXT("DATA WAS READED!!! -> %s"), _buffer);

			// Wait for Empty Call
			bool isEmptySended = false;
			while (!isEmptySended)
			{
				DWORD read;

				bool success = ReadFile(_pipeHandle, _buffer, BUFFER_SIZE * sizeof(TCHAR), &read, NULL);
				UE_LOG(LogTemp, Warning, TEXT("Reading Data..."));
				if (!success)
				{
					UE_LOG(LogTemp, Error, TEXT("Reading Data failed"));
					break;
				}
				else
				{
					const size_t size = strlen("Empty") + 1;
					wchar_t* message = new wchar_t[size];
					if (read == mbstowcs(message, "Empty", size))
					{
						isEmptySended = true;
					}
				}
			}
			UE_LOG(LogTemp, Warning, TEXT("DATA WAS READED!!! -> %s"), _buffer);

			// Send VillagerID to extern PyInterface
			DWORD written;
			WriteFile(_pipeHandle, villagerID, sizeof(villagerID), &written, NULL);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Client disconnected!"));
			CloseHandle(_pipeHandle);
			return 0;
		}		
	}

	return 0;
}
void MainNamedPipeAsync::Exit()
{
	StopPipeServer();
}
void MainNamedPipeAsync::Stop()
{
	StopPipeServer();
}

DWORD WINAPI InitialPyInterface(FString pipeName)
{
	return false;
}

/// <summary>
/// Stop the running named Pipe Server
/// </summary>
/// <returns>true: If server was closed | false: Closing failed</returns>
BOOL MainNamedPipeAsync::StopPipeServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Server Stopped"));
	FlushFileBuffers(_pipeHandle);
	DisconnectNamedPipe(_pipeHandle);
	return CloseHandle(_pipeHandle);
}
