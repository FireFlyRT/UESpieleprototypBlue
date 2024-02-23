// Fill out your copyright notice in the Description page of Project Settings.

#include "CrypticHelper.h"
#include <fstream>

CrypticHelper::CrypticHelper()
{
}

CrypticHelper::~CrypticHelper()
{
}

NeuralNetworkData* CrypticHelper::DecryptValue(FString* filePath)
{
	NeuralNetworkData* nnData = new NeuralNetworkData();

	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(**filePath))
	{
		FString data;

		if (FFileHelper::LoadFileToString(data, **filePath))
		{
			TSharedPtr<FJsonObject> jsonObject;

			if (FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(data), jsonObject))
			{
				const FString valueActionName = L"action";
				int32 jsonActionValue = jsonObject->GetIntegerField(valueActionName);

				const FString valueMovementXName = L"moveX";
				double jsonMovementXValue = jsonObject->GetNumberField(valueMovementXName);
				const FString valueMovementYName = L"moveY";
				double jsonMovementYValue = jsonObject->GetNumberField(valueMovementYName);

				const FString valueRotationName = L"rotX";
				double jsonRotationValue = jsonObject->GetIntegerField(valueRotationName);
				nnData->Action = jsonActionValue;
				nnData->Movement = FVector(jsonMovementXValue, jsonMovementYValue, 0);
				nnData->Rotation = FVector(0, 0, jsonRotationValue);
				nnData->IsUpdated = true;
			}
		}
	}

	return nnData;

	///*try 
	//{*/
	//	NeuralNetworkData* nnData = new NeuralNetworkData();
	//	int accidentalX = std::stoi(value.substr(0, 0));
	//	int moveSpeedX = std::stoi(value.substr(2, 4));
	//	int accidentalY = std::stoi(value.substr(6, 6));
	//	int moveSpeedY = std::stoi(value.substr(8, 10));

	//	if (accidentalX == 0) moveSpeedX *= -1;
	//	if (accidentalY == 0) moveSpeedY *= -1;

	//	accidentalX = std::stoi(value.substr(12, 12));
	//	int rotateSpeedX = std::stoi(value.substr(14, 16));
	//	accidentalY = std::stoi(value.substr(18, 18));
	//	int rotateSpeedY = std::stoi(value.substr(20, 22));

	//	if (accidentalX == 0) rotateSpeedX *= -1;
	//	if (accidentalY == 0) rotateSpeedY *= -1;

	//	int action = std::stoi(value.substr(24, 26));

	//	nnData->Movement = FVector(moveSpeedX, moveSpeedY, 0);
	//	nnData->Rotation = FVector(rotateSpeedX, rotateSpeedY, 0);
	//	nnData->Action = action;

	//	return nnData;
	///*}
	//catch (const std::exception& ex)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("NeuralNetwork Data Failed!!!"));
	//	return NeuralNetworkData(NULL);
	//}*/
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
						UE_LOG(LogTemp, Warning, TEXT("ASYNC"));
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