// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CCharacterController.h"
#include "CEnhancedCharacterController.generated.h"

UCLASS()
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

	ACVillager* Villager;
	
};
