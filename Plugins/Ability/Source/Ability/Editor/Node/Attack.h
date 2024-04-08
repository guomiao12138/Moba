// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityNode.h"
#include "Attack.generated.h"

/**
 * 
 */
UCLASS()
class ABILITY_API UAttack : public UAbilityNode
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	UAnimationAsset* Asset;

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void OnActiveNode() override;
	virtual bool OnDeActiveNode() override;
};
