// Fill out your copyright notice in the Description page of Project Settings.

#include "PythonInterface.h"


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

void PythonInterface::CreatePipeServer()
{
	_pipeHandle = CreateNamedPipe(
		TEXT("\\\\.\\pipe\\Pipe"),
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, // | FILE_FLAG_FIRST_PIPE_INSTANCE is not needed but forces CreateNamedPipe(..) to fail if the pipe already exists
		PIPE_UNLIMITED_INSTANCES,
		sizeof(_buffer) * 16,
		sizeof(_buffer) * 16,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL);
	UE_LOG(LogTemp, Warning, TEXT("Server Created!!!"));
}

/// <summary>
/// Starts a named Pipe Server
/// </summary>
bool PythonInterface::RunPipeServer()
{
	DWORD read;

	while (1)
	{
		if (_pipeHandle != INVALID_HANDLE_VALUE)
		{
			if (ConnectNamedPipe(_pipeHandle, NULL) != FALSE) // wait for someone to connect to the pipe
			{
				UE_LOG(LogTemp, Warning, TEXT("Connection esteblished with client"));
				while (ReadFile(_pipeHandle, _buffer, sizeof(_buffer) - 1, &read, NULL) != FALSE)
				{
					//TODO (MAJOR): Do smth with the data in buffer
					UE_LOG(LogTemp, Warning, TEXT("DATA WAS READED!!! %s"), _buffer);
				}

				return false;
			}
			else
			{
				StopPipeServer();
				return false;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Pipe invalid before Connecting"));
			return true;
		}
	}
	
}

/// <summary>
/// Stop the running named Pipe Server
/// </summary>
/// <returns>true: If server was closed | false: Closing failed</returns>
BOOL PythonInterface::StopPipeServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Server Stoped"));
	return DisconnectNamedPipe(_pipeHandle) && CloseHandle(_pipeHandle);
}
