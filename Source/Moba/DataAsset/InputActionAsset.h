// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DeveloperSettings.h"
#include "InputActionAsset.generated.h"

/**
 * 
 */
namespace ESteamSession
{
	enum Type
	{


	};
};

class FObjectPreSaveRootContext;
USTRUCT(BlueprintType)
struct FInputActionMapping
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FName ActionName;

	UPROPERTY(EditAnywhere)
	FKey BaseKey;

	UPROPERTY(EditAnywhere)
	FKey ModifyKey;
};



UCLASS(config = Moba, DefaultConfig, meta=(DisplayName="InputSetting"))
class MOBA_API UInputActionAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FString ConfigName;

	UPROPERTY(Config, EditAnywhere)
	TArray<FInputActionMapping> ActionMappings;

	UPROPERTY(Config, EditAnywhere)
	TArray<struct FInputAxisKeyMapping> AxisMappings;

	//virtual void Serialize(FArchive& Ar) override;
	virtual void PostLoad() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PreSaveRoot(FObjectPreSaveRootContext ObjectSaveContext) override;
#endif

	TArray<int> FindKeyIndex(FString source, FString flag);

};

