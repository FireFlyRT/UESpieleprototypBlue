// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class UESPIELEPROTOTYPBLUE_API SensorData
{
public:
	SensorData();
	~SensorData();

public:
	int ClassCategory;
	int TribeID;
	int LivePoints;
	int Stamina;
	int Strength;
	int Age;
	int Height;
	int Hunger;
	int Thurst;
	int PositionX;
	int PositionY;
	int PositionZ;
	int Distance;
	// Inventory Array
};
