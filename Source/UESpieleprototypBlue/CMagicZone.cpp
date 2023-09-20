// Fill out your copyright notice in the Description page of Project Settings.

#include "CMagicZone.h"

// Sets default values
ACMagicZone::ACMagicZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACMagicZone::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACMagicZone::NotifyActorBeginOverlap(AActor* other)
{
	Objects.Add((ACGameObject*)other);
}

void ACMagicZone::NotifyActorEndOverlap(AActor* other)
{
	Objects.Remove((ACGameObject*)other);
}

// Called every frame
void ACMagicZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACMagicZone::Accept()
{
	//DynMesh = ConstructDynamicType<ACDynamicMesh>(); ACDynamicMesh();
	//ResultMesh = ACDynamicMesh();

	NewTransform = FTransform(); 
	NewTransform.SetLocation(Objects[0]->Mesh->GetComponentLocation());

	ResultObject = GetWorld()->SpawnActor<ACGameObject>();
	ResultObject->SetActorTransform(NewTransform);
	ResultObject->AddComponentByClass(TSubclassOf<UStaticMeshComponent>(), false, ResultObject->GetTransform(), false);

	for (int i = 0; i < Objects.Num(); i++)
	{
		
		/*DynMesh.Append
		Objects[i]->Mesh->GetStaticMesh()*/
	}
}
