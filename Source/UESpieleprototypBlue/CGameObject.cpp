// Fill out your copyright notice in the Description page of Project Settings.


#include "CGameObject.h"

// Sets default values
ACGameObject::ACGameObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACGameObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACGameObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

