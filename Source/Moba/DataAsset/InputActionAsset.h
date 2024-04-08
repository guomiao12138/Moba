// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DeveloperSettings.h"
#include "InputActionAsset.generated.h"

/**
 * 
 */
class FObjectPreSaveRootContext;
struct FInputActionKeyMapping;
UCLASS(config = Moba, DefaultConfig, meta=(DisplayName="AAAAAA"))
class MOBA_API UInputActionAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Config, EditAnywhere)
	TArray<struct FInputActionKeyMapping> ActionMappings;

	UPROPERTY(Config, EditAnywhere)
	TArray<struct FInputAxisKeyMapping> AxisMappings;

	UPROPERTY(Config, EditAnywhere)
	int index = 0;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PreSaveRoot(FObjectPreSaveRootContext ObjectSaveContext) override;
#endif
};

