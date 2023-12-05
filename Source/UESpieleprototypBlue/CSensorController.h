// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SensorData.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CSensorController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UESPIELEPROTOTYPBLUE_API UCSensorController : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Collision")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;

private:
	SensorData* _sensorData;

public:	
	// Sets default values for this component's properties
	UCSensorController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	SensorData* GetSensorData();

	
};
