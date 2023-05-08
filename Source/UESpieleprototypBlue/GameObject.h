// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameObject.generated.h"

UCLASS()
class UESPIELEPROTOTYPBLUE_API AGameObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameObject();

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
