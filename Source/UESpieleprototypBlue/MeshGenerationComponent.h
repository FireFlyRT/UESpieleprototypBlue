#pragma once

#include "CoreMinimal.h"
#include "CGameObject.h"
#include "Components/ActorComponent.h"
#include "MeshGenerationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UESPIELEPROTOTYPBLUE_API UMeshGenerationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMeshGenerationComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	//UFUNCTION(BlueprintCallable)
	//ACGameObject* GenerateMesh(TArray<ACGameObject*> objects, ACGameObject* gameObject);
};
