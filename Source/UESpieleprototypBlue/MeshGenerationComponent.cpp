// Fill out your copyright notice in the Description page of Project Settings.
#include "MeshGenerationComponent.h"

// Sets default values for this component's properties
UMeshGenerationComponent::UMeshGenerationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UMeshGenerationComponent::BeginPlay()
{
	Super::BeginPlay();	
}

ACGameObject* UMeshGenerationComponent::GenerateMesh(TArray<ACGameObject*> objects)
{
	/*auto object = objects.Pop();

	auto mesh = object->Mesh->GetStaticMesh();
	(*mesh).GetRenderData()->LODResources[0].VertexBuffers.PositionVertexBuffer.VertexPosition(0);
	FMeshDescription* meshDescription = (*mesh).GetMeshDescription(0);
	


	AGameObject* newObject = NewObject<AGameObject>();
	auto mesh = newObject->Mesh->GetStaticMesh();
	
	(*mesh).GetRenderData()->LODResources[0].VertexBuffers.PositionVertexBuffer;*/
	// CreateMeshSection

	return nullptr;
}

