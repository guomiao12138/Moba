// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityNode.h"
#include "PrintNode.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Print"))
class ABILITY_API UPrintNode : public UAbilityNode
{
	GENERATED_BODY()
public:

	virtual void OnActiveNode() override;

};
