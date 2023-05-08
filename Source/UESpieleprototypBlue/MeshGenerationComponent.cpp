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

int UMeshGenerationComponent::GenerateMesh(TArray<GameObject*> objects)
{
	TArray<TArray<float>>* vertices = new TArray<TArray<float>>();
	TArray<TArray<float>>* uvs = new TArray<TArray<float>>();
	TArray<int>* triangles = new TArray<int>();

	//
	// for each object in objects
	// vertices += objects->Mesh->Vertices
	// uvs += objects->Mesh->Vertices
	//

	// Calcualte triangles

	// Add all to new Mesh

	return 0;
}

