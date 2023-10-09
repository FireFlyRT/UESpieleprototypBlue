// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CVillagerSpawnPoint.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPlanet.generated.h"

UCLASS()
class UESPIELEPROTOTYPBLUE_API ACPlanet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPlanet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ACVillagerSpawnPoint*> StartSpawns;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector WorldPosition;

};
