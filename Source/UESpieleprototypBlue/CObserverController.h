// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PythonInterface.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CObserverController.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UESPIELEPROTOTYPBLUE_API UCObserverController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCObserverController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	PythonInterface* _pyInterface;
};
