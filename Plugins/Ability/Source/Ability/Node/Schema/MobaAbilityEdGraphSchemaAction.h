// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobaAbilityEdGraphSchemaAction.generated.h"

/**
 * 
 */
USTRUCT()
struct FMobaAbilityEdGraphSchemaAction : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY()
	

	// Simple type info
	static FName StaticGetTypeId() { static FName Type("FMobaAbilityEdGraphSchemaAction_TargetNode"); return Type; }
	virtual FName GetTypeId() const override { return StaticGetTypeId(); }

	FMobaAbilityEdGraphSchemaAction()
		: FEdGraphSchemaAction()
	{}

	FMobaAbilityEdGraphSchemaAction(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping)
		: FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)
	{}

	// FEdGraphSchemaAction interface
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	// End of FEdGraphSchemaAction interface
};
