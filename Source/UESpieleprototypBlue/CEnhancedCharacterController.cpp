// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnhancedCharacterController.h"

static FRunnableThread* vThread;

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
}

void UCEnhancedCharacterController::SetVillagerId(FString* villagerId)
{
	FString* pipeName = new FString(TEXT("Villager"));
	*pipeName = pipeName->Append(*villagerId);
	const TCHAR* threadName = **pipeName;

	VillagerNamedPipeAsync* runnable = new VillagerNamedPipeAsync(pipeName, &NnData, &SensData);
	if (runnable != nullptr && threadName != nullptr)
		vThread = FRunnableThread::Create(runnable, threadName);
}

// Called every frame
void UCEnhancedCharacterController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (NnData.IsUpdated && Villager != nullptr)
	{
		NnData.IsUpdated = false;
		OnMove(NnData.Movement.X, NnData.Movement.Y);
		OnLook(NnData.Rotation);
		switch (NnData.Action)
		{
			case 1:
			{
				// OnPunch
				break;
			}
			case 2:
			{
				// Jump
				Villager->Jump();
				break;
			}
			case 3:
			{
				// OnPickUp();
				break;
			}
			case 4:
			{
				// OnThrowDown();
				break;
			}
			case 5:
			{
				// OnPlaceObject
				break;
			}
			case 6:
			{
				CreateMagicZone(Villager->GetTransform(), Villager->GetActorForwardVector());
				break;
			}
			case 7:
			{
				AcceptMagicZone();
				break;
			}
		}
		// Action == ?
		//		ObjectRotation

		// Get new SensorData
		UCSensorController* sensorController = Villager->GetComponentByClass<UCSensorController>();
		SensData = *sensorController->GetSensorData();
		if (&SensData != NULL)
			SensData.IsUpdated = true;
	}
}

void UCEnhancedCharacterController::DestroyComponent(bool bPromoteChildren)
{
	if (vThread != nullptr)
		vThread->Kill();
	Super::DestroyComponent(bPromoteChildren);
}
