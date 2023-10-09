// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ICharacterController.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CVillager.generated.h"

UCLASS()
class UESPIELEPROTOTYPBLUE_API ACVillager : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACVillager();

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsShiftActive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsStrgActive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsPunchActive;

	IICharacterController* CharacterController;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//UActorComponent* RightPunchCollider;

	// --- Villager Stats --- \\
	
	FString Name;
	int LivePoints;
	int Stamina;
	int Strength;
	// Animation[] UsableAnimations;
	//UIInventory Inventory;
	int Age;
	float Height;
	int Hunger;
	int Thurst;

	// --- Villager Stats --- \\

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
