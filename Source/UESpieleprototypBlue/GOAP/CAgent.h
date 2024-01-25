// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CAction.h"
#include "CSubGoal.h"
#include "Components/ActorComponent.h"
#include "CAgent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UESPIELEPROTOTYPBLUE_API UCAgent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCAgent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	TList<UCAction*>* Actions;
	TMap<CSubGoal*, int> Goals;

private:
//	CPlanner _planner;
	TQueue<UCAction*>* _actionQueue;
	UCAction* _currentAction;
	CSubGoal* _currentGoal;
	bool _actionInvoked;
};
