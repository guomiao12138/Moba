// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputActionAsset.generated.h"

/**
 * 
 */
UCLASS(config = Game, abstract)
class MOBA_API UDeafultSettingAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(Config, EditAnywhere)
	bool CanLoadDefault = true;

	virtual void PostInitProperties() override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PreSaveRoot(FObjectPreSaveRootContext ObjectSaveContext) override;
#endif
};

USTRUCT(BlueprintType)
struct FInputActionMapping
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EInputAction::Type> ActionName = EInputAction::Max;

	UPROPERTY(EditAnywhere)
	FKey BaseKey = EKeys::Invalid;

	UPROPERTY(EditAnywhere)
	FKey ModifyKey = EKeys::Invalid;
};

USTRUCT(BlueprintType)
struct FInputAxisMapping
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EInputAction::Type> ActionName = EInputAction::Max;

	UPROPERTY(EditAnywhere)
	float Scale = 1.f;

	UPROPERTY(EditAnywhere)
	FKey Key = EKeys::Invalid;
};


UCLASS(config = MobaInputSetting, configdonotcheckdefaults)
class MOBA_API UInputActionAsset : public UDeafultSettingAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(GlobalConfig, EditAnywhere)
	TArray<FInputActionMapping> ActionMappings;

	UPROPERTY(GlobalConfig, EditAnywhere)
	TArray<FInputAxisMapping> AxisMappings;

};

