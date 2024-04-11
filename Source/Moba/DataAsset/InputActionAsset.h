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
	FORCEINLINE FString GetName()\
	{\
		return GetEnumClass()->GetName();\
	}\
}\


UENUM(BlueprintType)
namespace EInputAction
{


	enum Type
	{
		MoveForawd,
		MoveRight,
		ClickPosition,
		Q,
		W,
		E,
		R,
		Max,
	};

}
ENUM_EX(EInputAction);

class FObjectPreSaveRootContext;
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


UCLASS(config = Moba, configdonotcheckdefaults, meta=(DisplayName="InputSetting"))
class MOBA_API UInputActionAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FString ConfigName;

	UPROPERTY(Config, EditAnywhere)
	TArray<FInputActionMapping> ActionMappings;

	UPROPERTY(Config, EditAnywhere)
	TArray<FInputAxisMapping> AxisMappings;

	virtual void Serialize(FArchive& Ar) override;
	virtual void PostLoad() override;
	virtual bool IsReadyForAsyncPostLoad() const override;
	//virtual void Serialize(FStructuredArchiveRecord Record) override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PreSaveRoot(FObjectPreSaveRootContext ObjectSaveContext) override;
#endif

	TArray<int> FindKeyIndex(FString source, FString flag);

};

