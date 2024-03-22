// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "Editor/BlueprintGraph/Classes/EdGraphSchema_K2.h"
#include "MobaAbilityNodeEdGraphSchema.generated.h"

/**
 * 
 */


class UAbilityNode;
class UMobaAbility;
struct FConnectionParams;
class UMobaAbilityEdGraph;
class FConnectionDrawingPolicy;

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
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;

	virtual class FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;
	//virtual bool CreatePromotedConnection(UEdGraphPin* PinA, UEdGraphPin* PinB) const override;
	//virtual FLinearColor GetSecondaryPinTypeColor(const FEdGraphPinType& PinType) const override { return FLinearColor::Red; };
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;
	/** End UEdGraphSchema Interface */

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

	UAbilityNode* CreateNode(UEdGraph* ParentGraph, const FVector2D Location);
};

