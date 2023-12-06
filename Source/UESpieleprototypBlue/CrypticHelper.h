// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NeuralNetworkData.h"
#include <string>

/**
 * 
 */
class UESPIELEPROTOTYPBLUE_API CrypticHelper
{
public:
	CrypticHelper();
	~CrypticHelper();

	static NeuralNetworkData* DecryptValue(std::string value);
	static std::string EncryptValue();
};
 