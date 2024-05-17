// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityNode.h"
#include "Root.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName = "Root"))
class ABILITY_API URoot : public UAbilityNode
{
	GENERATED_BODY()
	
public:
	URoot();

#if WITH_EDITOR
	virtual void AllocateDefaultPins() override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual UEdGraphPin* GetThenPin() override;
	virtual void CreateParamsPins() override {};
#endif	
};
