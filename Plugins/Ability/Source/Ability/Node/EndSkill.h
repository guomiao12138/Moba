// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityNode.h"
#include "EndSkill.generated.h"

/**
 * 
 */
UCLASS()
class UEndSkill : public UAbilityNode
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	virtual void AllocateDefaultPins() override;
	virtual void CreateParamsPins() override {};
#endif

	virtual void OnActiveNode() override;

};
