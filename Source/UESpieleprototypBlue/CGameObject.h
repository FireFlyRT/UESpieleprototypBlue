// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IGameObject.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CGameObject.generated.h"

UCLASS()
class UESPIELEPROTOTYPBLUE_API ACGameObject : public AActor, public IIGameObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACGameObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* otherActor) override;
	virtual void NotifyActorEndOverlap(AActor* otherActor) override;

public:
	virtual void OnPickUp(USkeletalMeshComponent* skeletalMesh) override;
	virtual void OnThrowDown(bool enablePhysics) override;
	virtual void UpdateMeshLocation() override;
	virtual void OnUse() override;
	virtual void OnPlace() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void OnHit(int demage);

	

	//	// --- Object Stats --- \\

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Position;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Durability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Temperature;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Weight;

	//	\\ --- Object Stats --- //

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsAttached;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsInMagicZone;
};
