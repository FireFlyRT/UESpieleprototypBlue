// Fill out your copyright notice in the Description page of Project Settings.

#include "CCharacterController.h"
#include "CVillager.h"
#include "EnhancedInputSubsystems.h"

// Sets default values for this component's properties
UCCharacterController::UCCharacterController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCCharacterController::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCCharacterController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCCharacterController::OnMove(float moveX, float moveY)
{
	Villager->AddMovementInput(Villager->GetMesh()->GetRelativeRotation().Vector().ForwardVector, moveX * MoveSpeed);
	Villager->AddMovementInput(Villager->GetMesh()->GetRelativeRotation().Vector().RightVector, moveY * MoveSpeed);
}

void UCCharacterController::SetVillager(ACVillager* villager)
{
	Villager = villager;
}

void UCCharacterController::OnLook(FVector rotation)
{
	Villager->AddControllerPitchInput(-rotation.Y * RotationSpeed);
	Villager->AddControllerYawInput(rotation.Z * RotationSpeed);
	Villager->AddControllerRollInput(rotation.X * RotationSpeed);
}

void UCCharacterController::OnPickUp(ACGameObject* object)
{
	ItemsRightHand.Add(object);
}

void UCCharacterController::OnThrowDown(ACGameObject* object)
{
	ItemsRightHand.Remove(object);
}

void UCCharacterController::CreateMagicZone(FTransform transform, FVector forwardVector)
{
	if (!MagicZone) 
	{
		FTransform newTransform = transform;
		newTransform.SetLocation(transform.GetLocation() + forwardVector * 100);
		newTransform.SetScale3D(FVector(1, 1, 1));
		MagicZone = GetWorld()->SpawnActor<ACMagicZone>();
		MagicZone->SetActorTransform(newTransform);
	}
}

void UCCharacterController::AcceptMagicZone()
{
	if (MagicZone)
	{
		MagicZone->Accept();
		MagicZone = nullptr;
		delete MagicZone;
	}
}
