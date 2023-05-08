// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CGameObject.generated.h"

UCLASS()
class UESPIELEPROTOTYPBLUE_API ACGameObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACGameObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsAttached;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Durability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Temperature;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Weight;
};
