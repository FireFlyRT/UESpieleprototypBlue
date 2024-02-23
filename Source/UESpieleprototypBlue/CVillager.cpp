// Fill out your copyright notice in the Description page of Project Settings.

#include "CVillager.h"
#include "CCharacterController.h"

// Sets default values
ACVillager::ACVillager()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void ACVillager::BeginPlay()
{
	Super::BeginPlay();

	CharacterController = Cast<IICharacterController>(GetComponentByClass<UCCharacterController>());
	
	CharacterController->SetVillager(this);
}

// Called every frame
void ACVillager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACVillager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

