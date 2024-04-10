// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DeveloperSettings.h"
#include "InputActionAsset.generated.h"

/**
 * 
 */
#define ENUM_EX(t) \
namespace t \
{ \
	FORCEINLINE const UEnum* GetEnumClass()\
	{\
		static const UEnum* enumClass = FindObject<UEnum>(nullptr, TEXT("/Script/Moba." #t), true);\
		return enumClass;\
	}\
	FORCEINLINE FName GetName(t::Type n)\
	{\
		FString name = GetEnumClass()->GetNameStringByValue((int)n);\
		return *name;\
	}\
	FORCEINLINE FName GetFullName(t::Type n)\
	{\
		FString name = GetEnumClass()->GetNameStringByValue((int)n);\
		name = GetEnumClass()->GenerateFullEnumName(*name);\
		return *name;\
	}\
	FORCEINLINE t::Type GetValueByName(FName name)\
	{\
		return (t::Type)GetEnumClass()->GetValueByName(name);\
	}\
	FORCEINLINE int GetValue(FString name)\
	{\
		return GetEnumClass()->GetValueByName(*name);\
	}\
}\


UENUM(BlueprintType)
namespace EInputAction
{


	enum Type
	{
		Q,
		W,
		E,
		R,
	};

}
ENUM_EX(EInputAction);

class FObjectPreSaveRootContext;
USTRUCT(BlueprintType)
struct FInputActionMapping
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EInputAction::Type> ActionName;

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

