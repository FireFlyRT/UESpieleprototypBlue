// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnhancedCharacterController.h"
#include "VillagerNamedPipeAsync.h"
#include "NeuralNetworkData.h"

UCEnhancedCharacterController::UCEnhancedCharacterController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UCEnhancedCharacterController::BeginPlay()
{
	Super::BeginPlay();

	FString pipeName = "Villager";
	pipeName.Append(VillagerID);
	wchar_t* threadName = pipeName.GetCharArray().GetData();
	VillagerNamedPipeAsync* runnable = new VillagerNamedPipeAsync(pipeName, _nnData, _isNnDataUpdated);
	/*_thread =*/ FRunnableThread::Create(runnable, threadName);
}

// Called every frame
void UCEnhancedCharacterController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (*_isNnDataUpdated)
	{
		*_isNnDataUpdated = false;
		OnMove(_nnData->Movement.X, _nnData->Movement.Y);
		// Send Data to Character for Move / Action / etc.
	}

	// Collect SensorData
	// Per Pointer to the Interface?
}

// VON INTERFACE ZU CHARACTER
// Input von VillagerPipe
// Daten kommen von PyInterface 
//  
// Über Pointer Variable hier her
// Mit bool Pointer in Update/Tick
// 
// 