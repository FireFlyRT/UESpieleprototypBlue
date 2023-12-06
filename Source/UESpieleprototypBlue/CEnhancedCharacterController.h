// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NeuralNetworkData.h"
#include "CSensorController.h"
#include "VillagerNamedPipeAsync.h"
#include "CVillager.h"
#include "SensorData.h"
#include "CoreMinimal.h"
#include "CCharacterController.h"
#include "CEnhancedCharacterController.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UESPIELEPROTOTYPBLUE_API UCEnhancedCharacterController : public UCCharacterController
{
	GENERATED_BODY()


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Sets default values for this component's properties
	UCEnhancedCharacterController();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void DestroyComponent(bool bPromoteChildren) override;
	void SetVillagerId(FString* villagerId);

public:
	FRunnableThread* _thread;
	ACVillager* Villager;
	NeuralNetworkData NnData = NeuralNetworkData();
	SensorData SensData = SensorData();
};
