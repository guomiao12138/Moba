// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "MyDeveloperSettings.generated.h"

/**
 * config=Input, defaultconfig
 */
UCLASS(config = Moba, defaultconfig, meta = (DisplayName = "AAAAAA"))
class MOBA_API UMyDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Config, EditAnywhere)
	FString aaa = "aa";
};

//UCLASS(config = Game)
//class AMyConfigActor : public UObject
//{
//	GENERATED_BODY()
//
//	UPROPERTY(Config)
//	int32 MyConfigVariable;
//};