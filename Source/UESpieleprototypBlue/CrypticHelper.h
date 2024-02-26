// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NeuralNetworkData.h"
#include "Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"
#include <string>
#include "SensorData.h"
#include "StatData.h"
#include "RewardData.h"

/**
 * 
 */
class UESPIELEPROTOTYPBLUE_API CrypticHelper
{
public:
	CrypticHelper();
	~CrypticHelper();

	static void DecryptValue(FString* filePath, NeuralNetworkData* nnData);
	static std::string EncryptValue(SensorData* sensorData, StatData* statData, RewardData* rewardData);
	static void WriteJsonToFile(std::string json, std::string filename, bool isAsync);

	static TArray<FActionToken> Actions;
};
 