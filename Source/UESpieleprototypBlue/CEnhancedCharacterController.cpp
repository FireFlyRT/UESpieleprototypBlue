// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnhancedCharacterController.h"

static FRunnableThread* vThread;

UCEnhancedCharacterController::UCEnhancedCharacterController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; 

	NnData = new NeuralNetworkData();
	SensData = new SensorData();
	StatsData = new StatData();
	RewData = new RewardData();
}

// Called when the game starts
void UCEnhancedCharacterController::BeginPlay()
{
	Super::BeginPlay();
}

void UCEnhancedCharacterController::SetVillagerId(FString* villagerId)
{
	StatsData->ClassCategory = 0;
	FString tribeID = villagerId->Mid(1, 1);
	StatsData->TribeID = FCString::Atoi(*tribeID);
	UE_LOG(LogTemp, Warning, TEXT("TribeID: %s"), *tribeID)
	FString villager = FString("Villager");
	std::wstring pipeName = std::wstring(*villager);
	pipeName.append(**villagerId);
	const TCHAR* threadName = pipeName.c_str();

	VillagerNamedPipeAsync* runnable = new VillagerNamedPipeAsync(new FString(pipeName.c_str()), NnData, SensData, StatsData, RewData);
	if (runnable != nullptr && threadName != nullptr)
		vThread = FRunnableThread::Create(runnable, threadName);
}

// Called every frame
void UCEnhancedCharacterController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if (NnData->IsUpdated && Villager != nullptr)
	//{
		NnData->IsUpdated = false;
		OnMove(NnData->Movement.X, NnData->Movement.Y);
		OnLook(NnData->Rotation);
		//UE_LOG(LogTemp, Warning, TEXT("MovementX: %f"), NnData->Movement.X)
		switch (NnData->Action)
		{
			case 1:
			{
				OnPunchDelegate.Broadcast();
				break;
			}
			case 2:
			{
				// Jump
				Villager->Jump();
				break;
			}
			case 3:
			{
				// OnPickUp();
				break;
			}
			case 4:
			{
				// OnThrowDown();
				break;
			}
			case 5:
			{
				// OnPlaceObject
				break;
			}
			case 6:
			{
				CreateMagicZone(Villager->GetTransform(), Villager->GetActorForwardVector());
				break;
			}
			case 7:
			{
				AcceptMagicZone();
				break;
			}
		}
		// Action == ?
		//		ObjectRotation

		// Get new SensorData
		//UCSensorController* sensorController = Villager->GetComponentByClass<UCSensorController>();
		//SensData = sensorController->GetSensorData();
		//if (&SensData != NULL)
		//	SensData->IsUpdated = true;
	//}
	//else
	//	UE_LOG(LogTemp, Error, TEXT("ICH WILL MICH NICHT BEWEGEN WEIL WEGEN BAUM!!! Update: %s"), NnData.IsUpdated);
}

void UCEnhancedCharacterController::SetSensorData(int classCategory, int tribeID, int livePoints, int stamina, int strength, 
	int age, int height, int hunger, int thurst, int positionX, int positionY, int positionZ, int distance)
{
	SensData->ClassCategory = classCategory;
	SensData->TribeID = tribeID;
	SensData->LivePoints = livePoints;
	SensData->Stamina = stamina;
	SensData->Strength = strength;
	SensData->Age = age;
	SensData->Height = height;
	SensData->Hunger = hunger;
	SensData->Thurst = thurst;
	SensData->PositionX = positionX;
	SensData->PositionY = positionY;
	SensData->PositionZ = positionZ;
	SensData->Distance = distance;
}

void UCEnhancedCharacterController::SetStatData(int livePoints, int stamina, int strength, 
	int age, int height, int hunger, int thurst, int positionX, int positionY, int positionZ)
{
	StatsData->LivePoints = livePoints;
	StatsData->Stamina = stamina;
	StatsData->Strength = strength;
	StatsData->Age = age;
	StatsData->Height = height;
	StatsData->Hunger = hunger;
	StatsData->Thurst = thurst;
	StatsData->PositionX = positionX;
	StatsData->PositionY = positionY;
	StatsData->PositionZ = positionZ;
}

void UCEnhancedCharacterController::SetRewardData(int reward, bool addition)
{
	if (addition)
	{
		RewData->Reward += reward;
	}
	else 
	{
		RewData->Reward = reward;
	}
}

void UCEnhancedCharacterController::DestroyComponent(bool bPromoteChildren)
{
	if (vThread != nullptr)
		vThread->Kill();
	Super::DestroyComponent(bPromoteChildren);
}
