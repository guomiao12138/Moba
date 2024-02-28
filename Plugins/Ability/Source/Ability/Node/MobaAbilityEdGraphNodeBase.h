// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "Engine/MemberReference.h"
#include "Editor/BlueprintGraph/Classes/K2Node.h"
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


	FName FuncName;
	FName Tooltip;

public:


	void Init(FName fucnname, FName tooltip);
	//virtual void SetFromFunction(const UFunction* Function);

	virtual void AllocateDefaultPins() override;
	// �ڵ��Title
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	// �ڵ�Title����ɫ
	virtual FLinearColor GetNodeTitleColor() const override;
	// Tooltip����
	virtual FText GetTooltipText() const override;

	virtual UObject* GetJumpTargetForDoubleClick() const override;

	virtual bool CanJumpToDefinition() const override;

	virtual void JumpToDefinition() const override;
};
