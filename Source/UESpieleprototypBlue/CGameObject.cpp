// Fill out your copyright notice in the Description page of Project Settings.


#include "CGameObject.h"
#include "CMagicZone.h"

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

void ACGameObject::NotifyActorBeginOverlap(AActor* otherActor)
{
	Super::NotifyActorBeginOverlap(otherActor);

	if (otherActor->GetClass() == TSubclassOf<ACMagicZone>())
	{
		Mesh->SetSimulatePhysics(false);
	}
}

void ACGameObject::NotifyActorEndOverlap(AActor* otherActor)
{
	Super::NotifyActorEndOverlap(otherActor);

	if (otherActor->GetClass() == TSubclassOf<ACMagicZone>())
	{
		Mesh->SetSimulatePhysics(true);
	}
}

void ACGameObject::OnPickUp(USkeletalMeshComponent* skeletalMesh)
{
	const FDetachmentTransformRules detachmentRules = FDetachmentTransformRules(EDetachmentRule::KeepRelative,
		EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, true);
	DetachFromActor(detachmentRules);

	Mesh->SetSimulatePhysics(false);
	Mesh->WakeAllRigidBodies();
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetOwner(skeletalMesh->GetOwner());

	const FAttachmentTransformRules attachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	AttachToComponent(skeletalMesh, attachmentRules, FName("HendHeldBoth"));

	IsAttached = true;
}

void ACGameObject::OnThrowDown(bool enablePhysics)
{
	IsAttached = false;

	const FDetachmentTransformRules detachmentRules = FDetachmentTransformRules(EDetachmentRule::KeepRelative,
		EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, true);
	DetachFromActor(detachmentRules);

	if (enablePhysics)
	{
		Mesh->SetSimulatePhysics(true);
	}

	Mesh->WakeAllRigidBodies();
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACGameObject::UpdateMeshLocation()
{
	Mesh->SetWorldLocation(RootComponent->GetComponentLocation());
}

// Called every frame
void ACGameObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsAttached)
	{
		UpdateMeshLocation();
	}
}

void ACGameObject::OnHit(int demage)
{
	Durability -= demage;
}

