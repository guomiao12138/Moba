// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
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
		functionName = *InMenuDesc.ToString();
	}


	FName functionName;

	// 核心函数
	virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode) override;

	UMobaAbilityEdGraphNodeBase* CreateNode();
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
