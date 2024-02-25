// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NeuralNetworkData.h"
#include "CSensorController.h"
#include "VillagerNamedPipeAsync.h"
#include "CVillager.h"
#include "CoreMinimal.h"
#include "CCharacterController.h"
#include "Delegates/Delegate.h"
#include "CEnhancedCharacterController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPunch);

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
	UFUNCTION(BlueprintCallable)
	void SetSensorData(int classCategory, int tribeID, int livePoints, int stamina, int strength, int age, 
		int height, int hunger, int thurst, int positionX, int positionY, int positionZ, int distance);
	UFUNCTION(BlueprintCallable)
	void SetStatData(int livePoints, int stamina, int strength, int age,
		int height, int hunger, int thurst, int positionX, int positionY, int positionZ);
	UFUNCTION(BlueprintCallable)
	void SetRewardData(int reward, bool addition = true);

public:
	FRunnableThread* VillagerThread;
	NeuralNetworkData* NnData;
	SensorData* SensData;
	StatData* StatsData;
	RewardData* RewData;	

	UPROPERTY(BlueprintReadWrite)
	ACVillager* Villager;
	UPROPERTY(BlueprintAssignable)
	FOnPunch OnPunchDelegate;
};
