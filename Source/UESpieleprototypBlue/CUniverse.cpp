// Fill out your copyright notice in the Description page of Project Settings.


#include "CUniverse.h"
#include "MainNamedPipeAsync.h"

// Sets default values
ACUniverse::ACUniverse()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACUniverse::BeginPlay()
{
	Super::BeginPlay();

	MainNamedPipeAsync* runnable = new MainNamedPipeAsync();
	if (runnable != nullptr)
	{
		_thread = FRunnableThread::Create(runnable, L"MainConnectionPipeThread");
	}
	
	for (int i = 0; i < Planets.Num(); i++)
	{
		FString* planetID = new FString();
		planetID->AppendInt(i);
		Planets[i]->SpawnVillagers(planetID);
	}
}

// Called every frame
void ACUniverse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACUniverse::BeginDestroy()
{
	if (_thread != nullptr)
	{
		_thread->Kill();
	}
	Super::BeginDestroy();
}

