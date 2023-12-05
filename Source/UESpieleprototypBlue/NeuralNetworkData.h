// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class UESPIELEPROTOTYPBLUE_API NeuralNetworkData
{
public:
	NeuralNetworkData();
	NeuralNetworkData(int null);
	~NeuralNetworkData();

public:
	int Null;
	bool IsUpdated;
	int Action;
	FVector Movement;
	FVector Rotation;

};
