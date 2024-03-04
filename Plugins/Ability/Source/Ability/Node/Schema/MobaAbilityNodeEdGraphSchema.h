// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "Editor/BlueprintGraph/Classes/EdGraphSchema_K2.h"
#include "MobaAbilityNodeEdGraphSchema.generated.h"

/**
 * 
 */


class UMobaAbilityEdGraphNodeBase;
class UMobaAbility;
UCLASS()
class ABILITY_API UMobaAbilityNodeEdGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()
	
public:
	UMobaAbilityNodeEdGraphSchema();

	UPROPERTY()
	TSubclassOf<UObject> AssetClass;
	/** Begin UEdGraphSchema Interface */

	// 右键空白处或者拖拽引脚调用函数
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	// 右键一个节点或者引脚出现的函数
	virtual void GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;
	virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override { return FLinearColor::White; };
	//virtual UEdGraphPin* DropPinOnNode(UEdGraphNode* InTargetNode, const FName& InSourcePinName, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection) const override;
	//virtual bool SupportsDropPinOnNode(UEdGraphNode* InTargetNode, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection, FText& OutErrorMessage) const { return true; }
	// 
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_A, TEXT(""));
	}
	
	//virtual bool CreatePromotedConnection(UEdGraphPin* PinA, UEdGraphPin* PinB) const override;
	//virtual FLinearColor GetSecondaryPinTypeColor(const FEdGraphPinType& PinType) const override { return FLinearColor::Red; };

	/** End UEdGraphSchema Interface */

	FName FuncName;


};

USTRUCT()
struct FMobaAbilityGraphSchemaAction : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY()

	FMobaAbilityGraphSchemaAction() :FEdGraphSchemaAction(
		NSLOCTEXT("Editor", "MobaAbilityCategory", "MobaAbility"),
		NSLOCTEXT("Editor", "MobaAbilityNodeName", "name"),
		NSLOCTEXT("Editor", "MobaAbilityTooltip", "ToolTip"),
		0
	) {}

	FMobaAbilityGraphSchemaAction(FText InNodeCategory, FText InMenuDesc, FText InToolTip)
		: FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), 0)
	{
		FunctionName = *InMenuDesc.ToString();
	}


	FName FunctionName;

	// 核心函数
	virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode) override;

	UMobaAbilityEdGraphNodeBase* CreateNode(UEdGraph* ParentGraph, const FVector2D Location);
};

USTRUCT()
struct ABILITY_API FMobaAbilityGraphSchemaAction_NewSubNode : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();

	/** Template of node we want to create */
	UPROPERTY()
	TObjectPtr<class UMobaAbilityEdGraphNodeBase> NodeTemplate;

	/** parent node */
	TObjectPtr<class UMobaAbilityEdGraphNodeBase> ParentNode;

	FMobaAbilityGraphSchemaAction_NewSubNode() :FEdGraphSchemaAction(
		NSLOCTEXT("Editor", "MobaAbilityCategory", "MobaAbility_NewSubNode"),
		NSLOCTEXT("Editor", "MobaAbilityNodeName", "name_NewSubNode"),
		NSLOCTEXT("Editor", "MobaAbilityTooltip", "ToolTip_NewSubNode"),
		0
	) {}

	//FMobaAbilityGraphSchemaAction_NewSubNode()
	//	: FEdGraphSchemaAction()
	//	, NodeTemplate(nullptr)
	//	, ParentNode(nullptr)
	//{}



	//~ Begin FEdGraphSchemaAction Interface
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	//virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2D Location, bool bSelectNewNode = true) override;
	//virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
};
