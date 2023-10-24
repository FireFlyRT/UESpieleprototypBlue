// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvironmentSpawner.h"

// Sets default values
AEnvironmentSpawner::AEnvironmentSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEnvironmentSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnObjects();
}

void AEnvironmentSpawner::SpawnObjects()
{
	FRandomStream rng = FRandomStream();

	for (int i = 0; i < MaxObjectsToSpawn; i++)
	{
		if (!(ObjectsSpawned >= MaxObjectsToSpawn))
		{
			ObjectsSpawned++;
		}

		rng.GenerateNewSeed();
		
		UClass* objectClass = SpawnableObjects[rng.RandRange(0, SpawnableObjects.Num() - 1)];

		float newX, newY, newZ;

		newX = rng.FRandRange(MinRandomPositionX, MaxRandomPositionX) + GetActorLocation().X;
		newY = rng.FRandRange(MinRandomPositionY, MaxRandomPositionY) + GetActorLocation().Y;
		newZ = rng.FRandRange(MinRandomPositionZ, MaxRandomPositionZ) + GetActorLocation().Z;

		const FVector location = FVector(newX, newY, newZ);

		const FTransform* transform = new FTransform(location);

		const FActorSpawnParameters parameter = FActorSpawnParameters();

		GetWorld()->SpawnActor(objectClass, transform, parameter);
	}
}

// Called every frame
void AEnvironmentSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

