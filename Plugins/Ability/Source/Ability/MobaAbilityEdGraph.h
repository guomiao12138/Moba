// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "MobaAbilityEdGraph.generated.h"

/**
 * 
 */
class UMobaAbilityEdGraphNodeBase;

UCLASS()
class ABILITY_API UMobaAbilityEdGraph : public UEdGraph
{
	GENERATED_BODY()
	
protected:
	UMobaAbilityEdGraphNodeBase* BeginNode;

public:
	UMobaAbilityEdGraph();

	 virtual void NotifyGraphChanged(const FEdGraphEditAction& Action) override;

	 virtual void BuildNode();

	 virtual UMobaAbilityEdGraphNodeBase* CreateBeginNode();



};
