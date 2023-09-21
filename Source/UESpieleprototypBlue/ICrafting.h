// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICrafting.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UICrafting : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UESPIELEPROTOTYPBLUE_API IICrafting
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void EnterCraftMode() PURE_VIRTUAL(UICrafting::EnterCraftMode);
	virtual void Place() PURE_VIRTUAL(UICrafting::Place);
	virtual void CreateMagicZone(FTransform transform, FVector forwardVector) PURE_VIRTUAL(UICrafting::CreateMagicZone);
	virtual void AcceptMagicZone() PURE_VIRTUAL(UICrafting::AcceptMagicZone);
};
