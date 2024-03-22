// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityNode.h"
#include "ChangeSpeed.generated.h"

/**
 * 
 */
UCLASS()
class ABILITY_API UChangeSpeed : public UAbilityNode
{
	GENERATED_BODY()
public:
	//virtual void AllocateDefaultPins() override;

	UPROPERTY(EditAnywhere)
	bool aa = false;

	UPROPERTY(EditAnywhere)
	float DuringTime = 2.f;

	UPROPERTY(EditAnywhere)
	float Speed = 0.f;

	FVector OldSpeed;

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void OnActiveNode() override;
	virtual bool OnDeActiveNode() override;
	virtual void Tick(float DeltaTime) override;
};
