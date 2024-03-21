// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "MobaAbilityEdGraph.generated.h"

/**
 * 
 */
class UAbilityNode;
class UAbilityNode_Default;
UCLASS()
class ABILITY_API UMobaAbilityEdGraph : public UEdGraph
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	TMap<FName, UAbilityNode_Default*> EventNodeMap;

public:
	UMobaAbilityEdGraph();

	 virtual void NotifyGraphChanged(const FEdGraphEditAction& Action) override;

	 virtual void BuildNode();

	 void ActiveEventNode(FName eventname);

	 virtual UAbilityNode* CreateDefaultNode(FName eventname);

	 
	 UAbilityNode_Default* GetRootNode() { return EventNodeMap[TEXT("Root")]; };
};
