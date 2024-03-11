// Fill out your copyright notice in the Description page of Project Settings.

#include "CrypticHelper.h"
#include <fstream>

CrypticHelper::CrypticHelper()
{
}

CrypticHelper::~CrypticHelper()
{
}

void CrypticHelper::DecryptValue(FString* filePath, NeuralNetworkData* nnData)
{
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(**filePath))
	{
		FString data;

		if (FFileHelper::LoadFileToString(data, **filePath))
		{
			TSharedPtr<FJsonObject> jsonObject;

			if (FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(data), jsonObject))
			{
				FString valueActionName = "action";
				int32 jsonActionValue = jsonObject->GetIntegerField(valueActionName);

				FString valueMovementXName = "moveX";
				double jsonMovementXValue = jsonObject->GetNumberField(valueMovementXName);
				FString valueMovementYName = "moveY";
				double jsonMovementYValue = jsonObject->GetNumberField(valueMovementYName);

				FString valueRotationName = "rotZ";
				double jsonRotationValue = jsonObject->GetIntegerField(valueRotationName);
				nnData->Action = jsonActionValue;
				nnData->Movement = FVector(jsonMovementXValue, jsonMovementYValue, 0);
				nnData->Rotation = FVector(0, 0, jsonRotationValue);
				nnData->IsUpdated = true;
			}
		}
	}
}

std::string CrypticHelper::EncryptValue(SensorData* sensorData, StatData* statData, RewardData* rewardData)
{
	TArray<TSharedPtr<FJsonValue>> sensItems;
	sensItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(sensorData->ClassCategory))));
	sensItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(sensorData->TribeID))));
	sensItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(sensorData->LivePoints))));
	sensItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(sensorData->Stamina))));
	sensItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(sensorData->Strength))));
	sensItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(sensorData->Age))));
	sensItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(sensorData->Height))));
	sensItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(sensorData->Hunger))));
	sensItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(sensorData->Thurst))));
	sensItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(sensorData->PositionX))));
	sensItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(sensorData->PositionY))));
	sensItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(sensorData->PositionZ))));
	sensItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(sensorData->Distance))));

	TArray<TSharedPtr<FJsonValue>> statItems;
	statItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(statData->ClassCategory))));
	statItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(statData->TribeID))));
	statItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(statData->LivePoints))));
	statItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(statData->Stamina))));
	statItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(statData->Strength))));
	statItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(statData->Age))));
	statItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(statData->Height))));
	statItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(statData->Hunger))));
	statItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(statData->Thurst))));
	statItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(statData->PositionX))));
	statItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(statData->PositionY))));
	statItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(statData->PositionZ))));

	TArray<TSharedPtr<FJsonValue>> rewItems;
	rewItems.Add(MakeShareable(new FJsonValueString(FString::FromInt(rewardData->Reward))));

	TSharedRef<FJsonObject> jsonObject = MakeShareable(new FJsonObject);
	jsonObject->SetArrayField("SensorData", sensItems);
	jsonObject->SetArrayField("StatData", statItems);
	jsonObject->SetArrayField("RewardData", rewItems);
	
	FString outputString;
	TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&outputString);
	FJsonSerializer::Serialize(jsonObject, writer);

	return TCHAR_TO_UTF8(*outputString);
}

void CrypticHelper::WriteJsonToFile(std::string json, std::string filename, bool isAsync = false)
{
	if (isAsync)
	{
		AsyncTask(ENamedThreads::AnyHiPriThreadNormalTask, [json, filename]()
			{
				AsyncTask(ENamedThreads::GameThread, [json, filename]()
					{
						std::ofstream writeStream(filename);
						writeStream << json;
						writeStream.close();
					});
			});
	}
	else
	{
		std::ofstream writeStream(filename);
		writeStream << json;
		writeStream.close();
	}
}