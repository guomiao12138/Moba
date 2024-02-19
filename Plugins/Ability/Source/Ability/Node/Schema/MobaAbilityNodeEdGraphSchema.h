// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "MobaAbilityNodeEdGraphSchema.generated.h"

/**
 * 
 */



UCLASS()
class ABILITY_API UMobaAbilityNodeEdGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()
	
public:

	/** Begin UEdGraphSchema Interface */

	// 右键空白处或者拖拽引脚调用函数
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	// 右键一个节点或者引脚出现的函数
	virtual void GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;

	/** End UEdGraphSchema Interface */

};

USTRUCT()
struct FMobaAbilityGraphSchemaAction : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY()

public:

	FMobaAbilityGraphSchemaAction() :FEdGraphSchemaAction(
		NSLOCTEXT("Editor", "MobaAbilityCategory", "MobaAbility"),
		NSLOCTEXT("Editor", "MobaAbilityNodeName", "name"),
		NSLOCTEXT("Editor", "MobaAbilityTooltip", "ToolTip"),
		0
	) {}

	// 核心函数
	virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode) override;
};

USTRUCT()
struct ABILITY_API FMobaAbilityGraphSchemaAction_NewSubNode : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();

	/** Template of node we want to create */
	UPROPERTY()
	TObjectPtr<class UMobaAbilityEdGraphNodeBase> NodeTemplate;

	/** parent node */
	UPROPERTY()
	TObjectPtr<class UMobaAbilityEdGraphNodeBase> ParentNode;

	FMobaAbilityGraphSchemaAction_NewSubNode()
		: FEdGraphSchemaAction()
		, NodeTemplate(nullptr)
		, ParentNode(nullptr)
	{}

	FMobaAbilityGraphSchemaAction_NewSubNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping)
		: FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)
		, NodeTemplate(nullptr)
		, ParentNode(nullptr)
	{}

	//~ Begin FEdGraphSchemaAction Interface
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2D Location, bool bSelectNewNode = true) override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	//~ End FEdGraphSchemaAction Interface
};
