// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobaAbilityEdGraphNodeBase.h"
#include "MobaAbilityNode_Default.generated.h"

/**
 * 
 */
UCLASS()
class ABILITY_API UMobaAbilityNode_Default : public UMobaAbilityEdGraphNodeBase
{
	GENERATED_BODY()
	
public:
	UMobaAbilityNode_Default();
	virtual void AllocateDefaultPins() override;
	virtual FLinearColor GetNodeTitleColor() const override;
};
