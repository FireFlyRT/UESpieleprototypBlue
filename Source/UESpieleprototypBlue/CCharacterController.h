// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CGameObject.h"
#include "ICharacterController.h"
#include "ICrafting.h"
#include "IDemagable.h"
#include "IInventory.h"
#include "CVillager.h"
#include "CMagicZone.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CCharacterController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UESPIELEPROTOTYPBLUE_API UCCharacterController : public UActorComponent, 
	public IICharacterController, public IICrafting, public IIDemagable, public IIInventory
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCCharacterController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	virtual void OnMove(float moveX, float moveY) override;
	UFUNCTION(BlueprintCallable)
	virtual void SetVillager(ACVillager* villager) override;
	UFUNCTION(BlueprintCallable)
	virtual void OnLook(FVector rotation) override;
	UFUNCTION(BlueprintCallable)
	virtual void OnPickUp(ACGameObject* object) override;
	UFUNCTION(BlueprintCallable)
	virtual void OnThrowDown(ACGameObject* object) override;
	UFUNCTION(BlueprintCallable)
	virtual void CreateMagicZone(FTransform transform, FVector forwardVector) override;
	UFUNCTION(BlueprintCallable)
	virtual void AcceptMagicZone() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACVillager* Villager;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//List
	TArray<ACGameObject*> ItemsRightHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//List
	TArray<ACGameObject*> ItemsLeftHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//MagicZone
	ACMagicZone* MagicZone;
};
