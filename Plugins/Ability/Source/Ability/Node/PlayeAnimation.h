// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityNode.h"
#include "PlayeAnimation.generated.h"

/**
 * 
 */
UCLASS()
class UPlayeAnimation : public UAbilityNode
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "AbilityNode")
	UAnimationAsset* Asset;


#if WITH_EDITOR
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
#endif
	virtual void OnActiveNode() override;
	virtual bool OnDeActiveNode() override;
};
