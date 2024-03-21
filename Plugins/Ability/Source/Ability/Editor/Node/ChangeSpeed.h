// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Editor/Node/AbilityNode.h"
#include "ChangeSpeed.generated.h"

/**
 * 
 */
UCLASS()
class ABILITY_API UChangeSpeed : public UAbilityNode
{
	GENERATED_BODY()
public:
	UAbilityNode_Default();
	virtual void AllocateDefaultPins() override;
	virtual FLinearColor GetNodeTitleColor() const override;
};
