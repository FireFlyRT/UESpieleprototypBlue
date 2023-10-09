// Fill out your copyright notice in the Description page of Project Settings.


#include "CVillagerSpawnPoint.h"

// Sets default values
ACVillagerSpawnPoint::ACVillagerSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACVillagerSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	FRandomStream* rng = new FRandomStream();

	for (int i = 0; i < StartAmount; i++)
	{
		GetWorld()->SpawnActor(SpawnableVillagers[rng->FRandRange(0, SpawnableVillagers.Num())]->GetClass());
	}
}

// Called every frame
//void ACVillagerSpawnPoint::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

