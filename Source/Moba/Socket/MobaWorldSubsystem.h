// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "MobaWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MOBA_API UMobaWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	virtual void Deinitialize();
};
