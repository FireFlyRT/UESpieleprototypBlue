// Fill out your copyright notice in the Description page of Project Settings.


#include "MainNamedPipeAsync.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <Json.h>
#include <string>
#include <filesystem>
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
	std::string jsonEmptyPath = std::string("/JSONData/Empty.json");
	int connectionCount = 0;
	for (;;)
	{
		if (std::filesystem::exists(jsonEmptyPath))
		{
			FString* result = new FString();
			char* r;
			std::ifstream file(jsonEmptyPath);
			file.read(r, file.gcount());
			FString* s = new FString(r);
			auto jsonData = FJsonStringReader::Create(*s);
			bool isReaded = false;
			EJsonNotation jsonNot;
			while (!isReaded)
			{
				if (jsonData->ReadNext(jsonNot))
				{
					FString value = jsonData->GetValueAsString();
					result->Append(value);
				}
				else
					isReaded = true;
			}
		}

		if (_pipeHandle == INVALID_HANDLE_VALUE)
		{
			UE_LOG(LogTemp, Warning, TEXT("MainPipe creation failed!!! Name: %s"), *_mainPipeName);
			connectionCount++;
			if (connectionCount > 100)
				return -1;
			continue;
		}

		while (ConnectNamedPipe(_pipeHandle, NULL) == FALSE);
		if (_pipeHandle != INVALID_HANDLE_VALUE)
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
			bool isEmptySended = false;
			DWORD read = DWORD();
			UE_LOG(LogTemp, Warning, TEXT("Before while"));
			while (1)
			{
				bool success = ReadFile(_pipeHandle, _buffer, BUFFER_SIZE * sizeof(TCHAR), &read, NULL);
				UE_LOG(LogTemp, Warning, TEXT("Reading Data... -> %s, %b"), read, success);
				if (!success && read == DWORD())
				{
					UE_LOG(LogTemp, Error, TEXT("Reading Data failed"));
					continue;
				}
				const size_t size = strlen("Empty") + 1;
				wchar_t* message = new wchar_t[size];
				if (read == mbstowcs(message, "Empty", size))
					isEmptySended = true;
				else
					villagerID = (wchar_t*)read;
				break;
			}
			UE_LOG(LogTemp, Warning, TEXT("DATA WAS READED!!! -> %s"), read);

			while (!isEmptySended)
			{
				read = DWORD();

				while (ReadFile(_pipeHandle, _buffer, BUFFER_SIZE * sizeof(TCHAR), &read, NULL) == FALSE);
				bool success = true;
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
			UE_LOG(LogTemp, Warning, TEXT("DATA WAS READED!!! -> %s"), read);

			// Send VillagerID to extern PyInterface
			if (isEmptySended)
			{
				DWORD written;
				WriteFile(_pipeHandle, villagerID, sizeof(villagerID), &written, NULL);
				isEmptySended = false;
			}
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
