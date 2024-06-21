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
UCLASS(Hidden)
class UMobaAnimGraphNode_Base : public UAnimGraphNode_Base
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECharacterType::Type> SlotName = ECharacterType::None;

	UPROPERTY(EditAnywhere, Category = Sync)
	FAnimationGroupReference AnimationGroupReference;

	UPROPERTY(EditAnywhere, Category = Sync)
	bool UseCustom;

	//UAnimGraphNode_Base
	virtual FText GetMenuCategory() const override;
	//virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostPasteNode() override;
	//UAnimGraphNode_Base

};

UCLASS(MinimalAPI, hideCategories = (Tag))
class UMobaAnimSequenceNode_Base : public UMobaAnimGraphNode_Base
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FMobaAnimNode_Sequence Node;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
};


UCLASS(MinimalAPI, hideCategories = (Tag, Coordinates))
class UMobaAnimBlendSpaceNode_Base : public UMobaAnimGraphNode_Base
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FMobaAnimNode_BlendSpace Node;

	UMobaAnimBlendSpaceNode_Base();
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
