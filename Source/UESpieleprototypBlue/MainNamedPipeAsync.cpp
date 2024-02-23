// Fill out your copyright notice in the Description page of Project Settings.


#include "MainNamedPipeAsync.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <stdio.h>
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
	FString projectFilePath = FPaths::GetProjectFilePath();
	FString projectPath = FPaths::GetPath(projectFilePath);
	UE_LOG(LogTemp, Warning, TEXT("Project Path: %s"), *projectPath);

	std::string jsonEmptyFile = TCHAR_TO_UTF8(*projectPath);
	std::string jsonEmptyPath = std::string("/PythonInterface/JSONData/Empty.json");
	jsonEmptyFile.append(jsonEmptyPath.c_str());

	bool emptyCommandFullfilled = false;
	for (;;)
	{
		if (!std::filesystem::exists(jsonEmptyFile))
		{
			emptyCommandFullfilled = false;
			continue;
		}

		if (emptyCommandFullfilled)
		{
			break;
		}

		//Start extern PyInterface
		// TODO (MAJOR): Copy .dll's in Build Folder!!!
		//system("..\\UESpieleprototypBlue\\x64\\Release\\PythonInterface.exe");
		//system("..\\UESpieleprototypBlue\\x64\\Debug\\PythonInterface.exe");
		UE_LOG(LogTemp, Warning, TEXT("PythonInterfaceProgram open"));

		UE_LOG(LogTemp, Warning, TEXT("Connection esteblished with a client"));

		std::ifstream emptyStream(jsonEmptyFile);
		std::string emptyResult((std::istreambuf_iterator<char>(emptyStream)), std::istreambuf_iterator<char>());
		UE_LOG(LogTemp, Warning, TEXT("From Path: %s | Value from json: %s"), jsonEmptyFile.c_str(), emptyResult.c_str());
		if (emptyResult.find(std::string("Empty")))
		{
			emptyCommandFullfilled = true;
		}
		emptyStream.close();
	}

	return 0;
}
