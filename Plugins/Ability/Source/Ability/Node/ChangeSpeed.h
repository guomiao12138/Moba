// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityNode.h"
#include "ChangeSpeed.generated.h"

/**
 * 
 */
UCLASS()
class UChangeSpeed : public UAbilityNode
{
	GENERATED_BODY()
public:
	//virtual void AllocateDefaultPins() override;

	UPROPERTY(EditAnywhere, Category = "AbilityNode")
	float DuringTime = 2.f;

	UPROPERTY(EditAnywhere, Category = "AbilityNode")
	float Speed = 0.f;

	UPROPERTY(EditAnywhere, Category = "AbilityNode | GameplayTags")
	TArray<struct FGameplayTag> GameplayTags;

	float OldSpeed;
#if WITH_EDITOR



	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
#endif
	virtual void OnActiveNode() override;
	virtual bool OnDeActiveNode() override;
	virtual void Tick(float DeltaTime) override;
};
