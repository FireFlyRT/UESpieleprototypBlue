// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CGameObject.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInventory.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIInventory : public UInterface
{
	GENERATED_BODY()
};

class UESPIELEPROTOTYPBLUE_API IIInventory
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnPickUp(ACGameObject* gameObject) PURE_VIRTUAL(UIInventory::OnPickUp);
	virtual void OnThrowDown(ACGameObject* gameObject) PURE_VIRTUAL(UIInventory::OnThrowDown);
};
