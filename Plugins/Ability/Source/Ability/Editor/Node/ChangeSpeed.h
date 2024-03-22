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
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
};
