// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CGameObject.h"
#include "GameFramework/Actor.h"
#include "EnvironmentSpawner.generated.h"

UCLASS()
class UESPIELEPROTOTYPBLUE_API AEnvironmentSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnvironmentSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ACGameObject*> SpawnableObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxObjectsToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ObjectsSpawned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MinRandomPositionX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxRandomPositionX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MinRandomPositionY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxRandomPositionY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MinRandomPositionZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxRandomPositionZ;
};
