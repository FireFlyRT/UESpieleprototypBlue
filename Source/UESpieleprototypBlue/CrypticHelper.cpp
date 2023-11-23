// Fill out your copyright notice in the Description page of Project Settings.


#include "CrypticHelper.h"

CrypticHelper::CrypticHelper()
{
}

CrypticHelper::~CrypticHelper()
{
}

NeuralNetworkData CrypticHelper::DecryptValue(std::string value)
{
	try 
	{
		NeuralNetworkData nnData = NeuralNetworkData();
		int accidentalX = std::stoi(value.substr(0, 0));
		int moveSpeedX = std::stoi(value.substr(2, 4));
		int accidentalY = std::stoi(value.substr(6, 6));
		int moveSpeedY = std::stoi(value.substr(8, 10));

		if (accidentalX == 0) moveSpeedX *= -1;
		if (accidentalY == 0) moveSpeedY *= -1;

		accidentalX = std::stoi(value.substr(12, 12));
		int rotateSpeedX = std::stoi(value.substr(14, 16));
		accidentalY = std::stoi(value.substr(18, 18));
		int rotateSpeedY = std::stoi(value.substr(20, 22));

		if (accidentalX == 0) rotateSpeedX *= -1;
		if (accidentalY == 0) rotateSpeedY *= -1;

		int action = std::stoi(value.substr(24, 26));

		return nnData;
	}
	catch (_exception ex)
	{
		UE_LOG(LogTemp, Warning, TEXT("NeuralNetwork Data Failed!!!"));
		return NeuralNetworkData(NULL);
	}
}

std::string CrypticHelper::EncryptValue()
{
	return std::string();
}
