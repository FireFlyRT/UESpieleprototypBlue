// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IDemagable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIDemagable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UESPIELEPROTOTYPBLUE_API IIDemagable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void GetDemage(int demage);
	virtual void DoDemage(int demage);
};
