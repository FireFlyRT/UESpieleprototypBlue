// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnhancedCharacterController.h"
#include "VillagerNamedPipeAsync.h"

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
	VillagerNamedPipeAsync* runnable = new VillagerNamedPipeAsync(pipeName);
	/*_thread =*/ FRunnableThread::Create(runnable, threadName);

}

// Called every frame
void UCEnhancedCharacterController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// VON INTERFACE ZU CHARACTER
// Input von VillagerPipe
// Daten kommen von PyInterface 
//  
// �ber Pointer Variable hier her?
// Mit bool Pointer in Update/Tick?
// 
// 