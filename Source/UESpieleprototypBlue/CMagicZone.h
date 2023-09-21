// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CDynamicMesh.h"
#include "CGameObject.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMagicZone.generated.h"

UCLASS()
class UESPIELEPROTOTYPBLUE_API ACMagicZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACMagicZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* other) override;
	virtual void NotifyActorEndOverlap(AActor* other) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Accept();

	TArray<ACGameObject*> Objects;
	//ACDynamicMesh ResultMesh;
	ACGameObject* ResultObject;
	//ACDynamicMesh DynMesh;
	FTransform NewTransform;
	UMaterial* MainMaterial;
};
