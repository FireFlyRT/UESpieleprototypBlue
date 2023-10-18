// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CVillager.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CVillagerSpawnPoint.generated.h"

UCLASS()
class UESPIELEPROTOTYPBLUE_API ACVillagerSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACVillagerSpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UClass*> SpawnableVillagers;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StartAmount;
};
