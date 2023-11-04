// Fill out your copyright notice in the Description page of Project Settings.


#include "CObserverController.h"
#include <iostream>

FRunnableThread* _thread;

// TODO (MAJOR): This needs to be transfered to another class or the final destination
class PyRunnableAsync : public FRunnable
{
public:
	PyRunnableAsync(){}
private:
	PythonInterface* _pyInterface;
	FString _threadId;
public:
	inline virtual bool Init() override
	{
		_pyInterface = new PythonInterface();
		return true;
	}
	inline virtual uint32 Run() override
	{
		for (;;)
		{
			//_pyInterface->CreatePipeServer();
			bool invalid = _pyInterface->RunPipeServer();
			if (invalid)
			{
				break;
			}
		}
		
		return 0;
	}
	inline virtual void Exit() override
	{
		_pyInterface->StopPipeServer();
	}
	inline virtual void Stop() override
	{
		_pyInterface->StopPipeServer();
	}
};
//

// Sets default values for this component's properties
UCObserverController::UCObserverController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCObserverController::BeginPlay()
{
	Super::BeginPlay();

	// TODO (MAJOR): Needs to be in the EnhancedCharacterController
	PyRunnableAsync* runnable = new PyRunnableAsync();
	std::wstring threadName(L"PyThread");
	_thread = FRunnableThread::Create(runnable, threadName.c_str());
	//
}

// TODO (MAJOR): Needs to be in the EnhancedCharacterController
void UCObserverController::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);
	UE_LOG(LogTemp, Warning, TEXT("OnComponentDestroyed ")); // DEBUG
	//_thread->Kill(); // Freezes the Game???

	delete _pyInterface;
	_pyInterface = nullptr;
}


// Called every frame
void UCObserverController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

