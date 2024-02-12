// Fill out your copyright notice in the Description page of Project Settings.


#include "MainNamedPipeAsync.h"
#include <iostream>
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
	std::string jsonVillagerPath = std::string("/JSONData/VillagerIDs.json");
	for (;;)
	{
		if (!std::filesystem::exists(jsonEmptyPath))
		{
			return -1;
		}

		UE_LOG(LogTemp, Warning, TEXT("Connection esteblished with a client"));
		// From VillagerPipe:
		// TODO (Major): In Queue (Or one Client at a Time), 

		//Start extern PyInterface
		// TODO (MAJOR): Copy .dll's in Build Folder!!!
		//system("..\\UESpieleprototypBlue\\x64\\Release\\PythonInterface.exe");
		//system("..\\UESpieleprototypBlue\\x64\\Debug\\PythonInterface.exe");
		UE_LOG(LogTemp, Warning, TEXT("PythonInterfaceProgram open"));

		FILE* emptyFile = nullptr;
		char emptyBuffer[255];
		size_t count = 0;
		fopen_s(&emptyFile, jsonEmptyPath.c_str(), "r");
		fread(emptyBuffer, sizeof(emptyBuffer) * sizeof(char), count, emptyFile);
		UE_LOG(LogTemp, Warning, TEXT("Value from json: %s"), emptyBuffer);
		std::string empty = std::string(emptyBuffer);
		if (empty.compare("Empty")) 
		{
			FILE* villagerFile = nullptr;
			char villagerBuffer[255];
			if (!std::filesystem::exists(jsonVillagerPath))
			{
				return -1;
			}
			// Get VillagerID from VillagerPipe
			count = 0;
			fopen_s(&villagerFile, jsonVillagerPath.c_str(), "r");
			fread(villagerBuffer, sizeof(villagerBuffer) * sizeof(char), count, villagerFile);
			UE_LOG(LogTemp, Warning, TEXT("Value from json: %s"), villagerBuffer);
			
			// Send VillagerID to extern PyInterface
			fopen_s(&villagerFile, jsonVillagerPath.c_str(), "w");
			fwrite(villagerBuffer, sizeof(villagerBuffer) * sizeof(char), count, villagerFile);
		}

		fclose(emptyFile);
		std::filesystem::remove();
	}

	return 0;
}
