// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimGraphNode_Base.h"
#include "Moba/Animation/Node/MobaAnimNode_base.h"
#include "MobaAnimGraphNode_Base.generated.h"

/**
 * 
 */
struct FAnimationGroupReference;
UCLASS(MinimalAPI, hideCategories=(Functions, Tag))
class UMobaAnimGraphNode_Base : public UAnimGraphNode_Base
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FName SlotName;

	UPROPERTY(EditAnywhere, Category = Sync)
	FAnimationGroupReference AnimationGroupReference;

	UPROPERTY()
	FMobaAnimNode_base Node;

	//UAnimGraphNode_Base
	virtual FText GetMenuCategory() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void GetBoundFunctionsInfo(TArray<TPair<FName, FName>>& InOutBindingsInfo) override;
	//UAnimGraphNode_Base
};
