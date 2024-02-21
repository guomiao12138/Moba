// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "MobaAbilityEdGraphNodeBase.generated.h"

/**
 * 
 */
UCLASS()
class ABILITY_API UMobaAbilityEdGraphNodeBase : public UEdGraphNode
{
	GENERATED_BODY()
	
public:
	virtual void AllocateDefaultPins() override;
	// �ڵ��Title
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	// �ڵ�Title����ɫ
	virtual FLinearColor GetNodeTitleColor() const override;
	// Tooltip����
	virtual FText GetTooltipText() const override;

<<<<<<< HEAD
	//virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
=======
	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
>>>>>>> 595b50cfd57cee54cfddcf2bb92eddc25d608d11
};
