// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CVillager.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICharacterController.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UICharacterController : public UInterface
{
	GENERATED_BODY()
};

class UESPIELEPROTOTYPBLUE_API IICharacterController
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnMove(float moveX, float moveY);
	virtual void SetVillager(ACVillager* villager);
	virtual void OnLook(FVector rotation);
};
