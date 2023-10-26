// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlanet.h"

// Sets default values
ACPlanet::ACPlanet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPlanet::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ACPlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlanet::SpawnVillagers(FString planetID)
{
	for (int i = 0; i < StartSpawns.Num() - 1; i++)
	{
		planetID.AppendInt(i);
		StartSpawns[i]->SpawnVillager(planetID);
	}
}

