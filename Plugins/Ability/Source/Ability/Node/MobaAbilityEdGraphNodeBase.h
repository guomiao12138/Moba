// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "Engine/MemberReference.h"
#include "MobaAbilityEdGraphNodeBase.generated.h"

/**
 * 
 */
UCLASS()
class ABILITY_API UMobaAbilityEdGraphNodeBase : public UEdGraphNode
{
	GENERATED_BODY()
	
protected:

	UPROPERTY()
	FMemberReference FunctionReference;

	virtual FText GetFunctionContextString() const;

	virtual void SetFromFunction(const UFunction* Function);

public:
	virtual void AllocateDefaultPins() override;
	// �ڵ��Title
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	// �ڵ�Title����ɫ
	virtual FLinearColor GetNodeTitleColor() const override;
	// Tooltip����
	virtual FText GetTooltipText() const override;

	//virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
};
