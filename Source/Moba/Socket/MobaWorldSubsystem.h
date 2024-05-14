// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "MobaWorldSubsystem.generated.h"

/**
 * 
 */
class UClient;
UCLASS()
class MOBA_API UClientPlayerSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
	
	UPROPERTY()
	UClient* Client;

public:


	void SendMsg(TArray<FString>& InArgs);

	virtual void Initialize(FSubsystemCollectionBase& Collection);

	virtual void Deinitialize();
};
