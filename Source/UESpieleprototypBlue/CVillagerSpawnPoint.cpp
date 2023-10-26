// Fill out your copyright notice in the Description page of Project Settings.


#include "CVillagerSpawnPoint.h"
#include "CEnhancedCharacterController.h"

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
}

// Called every frame
void ACVillagerSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACVillagerSpawnPoint::SpawnVillager(FString tribeID)
{
	FRandomStream* rng = new FRandomStream();

	for (int i = 0; i < StartAmount; i++)
	{
		tribeID.AppendInt(i); // VillagerID
		rng->GenerateNewSeed();
		AActor* actor = GetWorld()->SpawnActor(SpawnableVillagers[rng->FRandRange(0, SpawnableVillagers.Num())]);

		UCEnhancedCharacterController* enhController = actor->GetComponentByClass<UCEnhancedCharacterController>();
		// enhController->SetupAIFunctions(tribeID); Name?

		FVector location = GetActorLocation();
		location += FVector(rng->FRandRange(-1000, 1000), rng->FRandRange(-1000, 1000), 0);
		actor->SetActorLocation(location);
	}
}

