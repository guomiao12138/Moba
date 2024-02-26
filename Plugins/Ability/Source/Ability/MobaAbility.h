// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MobaAbility.generated.h"

/**
 * 
 */
UCLASS()
class ABILITY_API UMobaAbility : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FName AbilityName;

	UFUNCTION(BlueprintImplementableEvent)
	void Start();
	

	UFUNCTION()
	void AAAA(FName name);

	UFUNCTION()
	void CCCC(UAnimationAsset* asset);

	UFUNCTION()
	void XXXX();

	TObjectPtr<UEdGraph> EdGraph;
};
