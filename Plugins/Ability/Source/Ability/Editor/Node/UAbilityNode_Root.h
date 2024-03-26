// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityNode.h"
#include "UAbilityNode_Root.generated.h"

/**
 * 
 */
UCLASS()
class ABILITY_API UAbilityNode_Root : public UAbilityNode
{
	GENERATED_BODY()
	
public:
	UAbilityNode_Root();
	virtual void AllocateDefaultPins() override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual UEdGraphPin* GetThenPin() override;
	virtual void CreateParamsPins() override;
};
