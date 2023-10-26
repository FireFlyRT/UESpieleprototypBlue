// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PythonInterface.h"
#include "CoreMinimal.h"

/**
 * 
 */
class UESPIELEPROTOTYPBLUE_API VillagerNamedPipeAsync : public FRunnable
{
public:
	VillagerNamedPipeAsync();
	~VillagerNamedPipeAsync();

public:
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;
	virtual void Stop() override;
};
