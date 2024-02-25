// Fill out your copyright notice in the Description page of Project Settings.


#include "NeuralNetworkData.h"

NeuralNetworkData::NeuralNetworkData()
{
	Null = 1;
	IsUpdated = false;
	Action = 0;
	Movement = FVector(0, 0, 0);
	Rotation = FVector(0, 0, 0);
}

NeuralNetworkData::NeuralNetworkData(int null)
{
	Null = null;
	IsUpdated = false;
	Action = 0;
	Movement = FVector(0, 0, 0);
	Rotation = FVector(0, 0, 0);
}

NeuralNetworkData::~NeuralNetworkData()
{
}
