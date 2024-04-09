// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityNode.h"
#include "EndSkill.generated.h"

/**
 * 
 */
UCLASS()
class ABILITY_API UEndSkill : public UAbilityNode
{
	GENERATED_BODY()

public:
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void OnActiveNode() override;
	virtual void CreateParamsPins() override;
};
