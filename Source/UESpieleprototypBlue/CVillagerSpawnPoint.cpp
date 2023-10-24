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

	int startAmount = 5;

	for (int i = 0; i < 5; i++)
	{
		rng->GenerateNewSeed();
		AActor* actor = GetWorld()->SpawnActor(SpawnableVillagers[rng->FRandRange(0, SpawnableVillagers.Num())]);
		FVector location = GetActorLocation();
		location += FVector(rng->FRandRange(-1000, 1000), rng->FRandRange(-1000, 1000), 0);
		actor->SetActorLocation(location);
	}
}

// Called every frame
void ACVillagerSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

