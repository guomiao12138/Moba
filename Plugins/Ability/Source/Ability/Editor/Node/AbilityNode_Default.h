// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityNode.h"
#include "AbilityNode_Default.generated.h"

/**
 * 
 */
UCLASS()
class ABILITY_API UAbilityNode_Default : public UAbilityNode
{
	GENERATED_BODY()
	
public:
	UAbilityNode_Default();
	virtual void AllocateDefaultPins() override;
	virtual FLinearColor GetNodeTitleColor() const override;
};
