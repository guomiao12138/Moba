// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "SocketDeveloperSettings.generated.h"

UCLASS(config = SocketDeveloperSettings, defaultconfig, meta = (DisplayName = "MobaSoccket"))
class MOBA_API USocketDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	virtual FName GetContainerName() const override { return FName("Project"); }
	/** Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc. */
	virtual FName GetCategoryName() const override { return FName("Moba"); }
	/** The unique name for your section of settings, uses the class's FName. */
	virtual FName GetSectionName() const override { return FName("MobaSoccket"); }


	UPROPERTY(Config, EditAnywhere)
	FString ip = "127.0.0.1";

	UPROPERTY(Config, EditAnywhere)
	int port = 0;

	UPROPERTY(Config, EditAnywhere)
	float CheckAccpetRate = 1.f;
};
