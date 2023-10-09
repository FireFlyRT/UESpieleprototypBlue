// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CPlanet.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CUniverse.generated.h"

UCLASS()
class UESPIELEPROTOTYPBLUE_API ACUniverse : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACUniverse();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ACPlanet*> Planets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int TimeScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FDateTime DateTime;
};
