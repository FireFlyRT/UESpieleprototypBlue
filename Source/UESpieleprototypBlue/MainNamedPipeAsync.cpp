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
	for (;;)
	{
		_pipeHandle = CreateNamedPipe(
			_mainPipeName,
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, // | FILE_FLAG_FIRST_PIPE_INSTANCE is not needed but forces CreateNamedPipe(..) to fail if the pipe already exists
			PIPE_UNLIMITED_INSTANCES,
			BUFFER_SIZE,
			BUFFER_SIZE,
			NMPWAIT_USE_DEFAULT_WAIT,
			NULL);

		if (_pipeHandle == INVALID_HANDLE_VALUE)
		{
			UE_LOG(LogTemp, Warning, TEXT("MainPipe creation failed!!!"));
			return -1;
		}
		UE_LOG(LogTemp, Warning, TEXT("MainPipe-Server Created!!!"));

		if (ConnectNamedPipe(_pipeHandle, NULL) != FALSE)
		{
			UE_LOG(LogTemp, Warning, TEXT("Connection esteblished with a client"));

			/*FString pipeName = TEXT("BLA");
			VillagerNamedPipeAsync* runnable = new VillagerNamedPipeAsync(pipeName);
			std::wstring threadName(L"PyThread");
			HANDLE thread = FRunnableThread::Create(runnable, threadName.c_str());*/
			/*if (thread == NULL)
			{
				UE_LOG(LogTemp, Warning, TEXT("Thread creation failed!!!"));
				return -1;
			}
			else
			{
				CloseHandle(thread);
			}*/
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Client disconnected!"));
			CloseHandle(_pipeHandle);
			return false;
		}

		
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
		}
		UE_LOG(LogTemp, Warning, TEXT("DATA WAS READED!!! -> %s"), _buffer);
	}

	return 0;
}
void MainNamedPipeAsync::Exit()
{
	
}
void MainNamedPipeAsync::Stop()
{
	
}

DWORD WINAPI InitialPyInterface(FString pipeName)
{
	return false;
}
