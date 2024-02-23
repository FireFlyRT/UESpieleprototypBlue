// Fill out your copyright notice in the Description page of Project Settings.


#include "CSensorController.h"
#include "CEnhancedCharacterController.h"

// Sets default values for this component's properties
UCSensorController::UCSensorController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCSensorController::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCSensorController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<TArray<FHitResult>> allHitResults;

	FVector traceStart = GetOwner()->GetActorLocation();
	FCollisionQueryParams quaryParams;
	quaryParams.AddIgnoredActor(GetOwner());

	for (int i = 1; i < 2; i++)
	{
		FVector traceEnd = GetOwner()->GetActorForwardVector();
		traceEnd.X += 1.0f / i;
		traceEnd.Normalize();
		traceEnd += GetOwner()->GetActorLocation();
		traceEnd *= 1000.0f;
		TArray<FHitResult> hitResults;
		GetWorld()->LineTraceMultiByChannel(hitResults, traceStart, traceEnd, TraceChannelProperty, quaryParams);
		allHitResults.Add(hitResults);

		// Recursion to create traces on both sides of the excisting traces

		traceEnd = GetOwner()->GetActorLocation() + -GetOwner()->GetActorForwardVector();
		GetWorld()->LineTraceMultiByChannel(hitResults, traceStart, traceEnd, TraceChannelProperty, quaryParams);
		allHitResults.Add(hitResults);
		
		traceEnd = GetOwner()->GetActorLocation() + GetOwner()->GetActorRightVector();
		GetWorld()->LineTraceMultiByChannel(hitResults, traceStart, traceEnd, TraceChannelProperty, quaryParams);
		allHitResults.Add(hitResults);
		
		traceEnd = GetOwner()->GetActorLocation() + -GetOwner()->GetActorRightVector();
		GetWorld()->LineTraceMultiByChannel(hitResults, traceStart, traceEnd, TraceChannelProperty, quaryParams);
		allHitResults.Add(hitResults);
	}

	for (int i = 0; i < allHitResults.Num(); i++)
	{
		for (int j = 0; j < allHitResults[i].Num(); i++)
		{
			if (allHitResults[i][j].bBlockingHit && IsValid(allHitResults[i][j].GetActor()))
			{
				// Get all Data from Actor
				UCEnhancedCharacterController* eCharController = allHitResults[i][j].GetActor()->GetComponentByClass<UCEnhancedCharacterController>();
				if (!eCharController)
					continue;

				_sensorData->ClassCategory = eCharController->StatsData->ClassCategory;
				_sensorData->TribeID = eCharController->StatsData->TribeID;
				_sensorData->LivePoints = eCharController->StatsData->LivePoints;
				_sensorData->Stamina = eCharController->StatsData->Stamina;
				_sensorData->Strength = eCharController->StatsData->Strength;
				_sensorData->Age = eCharController->StatsData->Age;
				_sensorData->Height = eCharController->StatsData->Height;
				_sensorData->Hunger = eCharController->StatsData->Hunger;
				_sensorData->Thurst = eCharController->StatsData->Thurst;
				_sensorData->PositionX = eCharController->StatsData->PositionX;
				_sensorData->PositionY = eCharController->StatsData->PositionY;
				_sensorData->PositionZ = eCharController->StatsData->PositionZ;
				_sensorData->Distance = FVector::Dist(GetOwner()->GetActorLocation(), FVector(
					eCharController->StatsData->PositionX,
					eCharController->StatsData->PositionY,
					eCharController->StatsData->PositionZ));

				return;
			}
		}
	}

	if (allHitResults.Num() == 0)
	{
		_sensorData->ClassCategory = 0;
		_sensorData->TribeID = 0;
		_sensorData->LivePoints = 0;
		_sensorData->Stamina = 0;
		_sensorData->Strength = 0;
		_sensorData->Age = 0;
		_sensorData->Height = 0;
		_sensorData->Hunger = 0;
		_sensorData->Thurst = 0;
		_sensorData->PositionX = 0;
		_sensorData->PositionY = 0;
		_sensorData->PositionZ = 0;
		_sensorData->Distance = 0;
	}
}

SensorData* UCSensorController::GetSensorData()
{
	// Read all Data from Sensors

	// Get Count for all Classes
	// Get Data from closest

	return _sensorData;
}

