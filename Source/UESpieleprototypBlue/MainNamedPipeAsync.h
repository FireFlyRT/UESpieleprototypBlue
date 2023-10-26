// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PythonInterface.h"
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>

class UESPIELEPROTOTYPBLUE_API MainNamedPipeAsync : public FRunnable
{
public:
	MainNamedPipeAsync();
	~MainNamedPipeAsync();

private:
	HANDLE _pipeHandle = INVALID_HANDLE_VALUE;
	BOOL _connected = FALSE;
	TCHAR* _buffer;
	LPCTSTR _mainPipeName = TEXT("\\\\.\\pipe\\MainPipe");
	DWORD _threadID = 0;

public:
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;
	virtual void Stop() override;
};
