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

	TSharedPtr<class FDocumentTracker> DocumentManager;

	FName FuncName;
	FName Tooltip;

public:

	UMobaAbilityEdGraphNodeBase();
	//void Init(FName fucnname, FName tooltip);

	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FText GetTooltipText() const override;
	virtual UObject* GetJumpTargetForDoubleClick() const override;
	virtual bool CanJumpToDefinition() const override;
	virtual void JumpToDefinition() const override;


	virtual FText GetFunctionContextString() const;
	virtual void SetFromFunction(const UFunction* Function);
	void SetDoubleClickEvent(FSingleNodeEvent InSingleNodeEvent);


	//UFUNCTION()
	//void aaa();
	//TSharedPtr<SGraphEditor> OpenGraphAndBringToFront(UEdGraph* Graph, bool bSetFocus = true);
	static FSingleNodeEvent SingleNodeEvent;
};
