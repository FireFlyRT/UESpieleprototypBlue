// Fill out your copyright notice in the Description page of Project Settings.

#include "PythonInterface.h"

PythonInterface::PythonInterface()
{
	_pipeHandle = CreateNamedPipe(
		TEXT("\\\\.\\pipe\\Pipe"),
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, // FILE_FLAG_FIRST_PIPE_INSTANCE is not needed but forces CreateNamedPipe(..) to fail if the pipe already exists
		1,
		sizeof(_buffer) * 16,
		sizeof(_buffer) * 16,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL);

	UE_LOG(LogTemp, Warning, TEXT("Server Created!!!"));
}

PythonInterface::~PythonInterface()
{
	delete _pipeHandle;
	_pipeHandle = nullptr;
}

/// <summary>
/// Starts a named Pipe Server
/// </summary>
bool PythonInterface::RunPipeServer()
{
	bool connected = false;
	DWORD read;

	while (_pipeHandle != INVALID_HANDLE_VALUE)
	{
		if (ConnectNamedPipe(_pipeHandle, NULL) != FALSE) // wait for someone to connect to the pipe
		{
			connected = true;
			UE_LOG(LogTemp, Warning, TEXT("Connection esteblished with client"));
			while (ReadFile(_pipeHandle, _buffer, sizeof(_buffer) - 1, &read, NULL) != FALSE)
			{
				_buffer[read] = '\0'; // add terminating zero
				FString* bufferRead = new FString(_buffer);

				//TODO (MAJOR): Do smth with the data in buffer
				UE_LOG(LogTemp, Warning, TEXT("DATA WAS READED!!! %d"), bufferRead->Len());
			}
		}
	}

	if (connected)
	{
		StopPipeServer();
		UE_LOG(LogTemp, Warning, TEXT("Pipe deleted"));

		delete _pipeHandle;
		_pipeHandle = nullptr;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Wait Timeout"));

	return connected;
}

/// <summary>
/// Stop the running named Pipe Server
/// </summary>
/// <returns>true: If server was closed | false: Closing failed</returns>
BOOL PythonInterface::StopPipeServer()
{
	return DisconnectNamedPipe(_pipeHandle);
}
