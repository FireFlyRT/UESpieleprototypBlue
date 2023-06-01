// Fill out your copyright notice in the Description page of Project Settings.
#include "MeshGenerationComponent.h"

// Sets default values for this component's properties
UMeshGenerationComponent::UMeshGenerationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UMeshGenerationComponent::BeginPlay()
{
	Super::BeginPlay();	
}

ACGameObject* UMeshGenerationComponent::GenerateMesh(TArray<ACGameObject*> objects)
{
	ACGameObject* _gameObject = NewObject<ACGameObject>();
	UStaticMeshComponent* _meshComponent = NewObject<UStaticMeshComponent>();
	UStaticMesh* _mesh = NewObject<UStaticMesh>();

	_mesh->SetRenderData(TUniquePtr<FStaticMeshRenderData>(new FStaticMeshRenderData()));
	FStaticMeshRenderData* meshData = _mesh->GetRenderData();
	meshData->LODResources.Add(new FStaticMeshLODResources());

	FPositionVertexBuffer vertexBuffer = meshData->LODResources[0].VertexBuffers.PositionVertexBuffer;
	FRawStaticIndexBuffer indexBuffer = meshData->LODResources[0].IndexBuffer;

	for (int objectIndex = 0; objectIndex < objects.Num(); objectIndex++)
	{
		UStaticMesh* objectMesh = objects[objectIndex]->Mesh->GetStaticMesh();
		FPositionVertexBuffer objectPosBuffer = objectMesh->GetRenderData()->LODResources[0].VertexBuffers.PositionVertexBuffer;
		FRawStaticIndexBuffer objectIndexBuffer = objectMesh->GetRenderData()->LODResources[0].IndexBuffer;
		FStaticMeshBuildVertex* vertexBuild = new FStaticMeshBuildVertex();

		for (unsigned int i = 0; i < objectPosBuffer.GetNumVertices(); i++)
		{
			vertexBuild->Position = objectPosBuffer.VertexPosition(i);
			
			vertexBuffer.AppendVertices(vertexBuild, 1);
		}

		for (int i = 0; i < objectIndexBuffer.GetNumIndices(); i++)
		{
			objectIndexBuffer.GetIndex(i);
			const uint32* indexPointer = new const uint32(objectIndexBuffer.GetIndex(i));
			indexBuffer.AppendIndices(indexPointer, 1);
		}
	}

	_meshComponent->SetStaticMesh(_mesh);
	_gameObject->Mesh = _meshComponent;

	return _gameObject;
}

