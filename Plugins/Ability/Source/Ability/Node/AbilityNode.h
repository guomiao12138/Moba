// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "Editor/BlueprintGraph/Classes/K2Node.h"
#include "AbilityNode.generated.h"

/**
 * 
 */
UCLASS()
class UAbilityNode : public UEdGraphNode
{
	GENERATED_BODY()
	
protected:

public:

	UPROPERTY(EditAnywhere, SimpleDisplay)
	bool CanTick = false;
	bool Succeed = false;
	int OutInputIndex = 0;

	UAbilityNode();

	//UEdGraphNode
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FText GetTooltipText() const override;
	virtual UObject* GetJumpTargetForDoubleClick() const override;
	virtual bool CanJumpToDefinition() const override;
	virtual void JumpToDefinition() const override;
	virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;
	virtual void PostPlacedNewNode() override;
	virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;
	//UEdGraphNode
	virtual void CreateParamsPins();
	UEdGraphPin* GetExecutePin();
	virtual UEdGraphPin* GetThenPin();

	virtual void Tick(float DeltaTime);

	virtual void OnActiveNode();
	virtual bool OnDeActiveNode() { return true; };

	UPROPERTY()
	TArray<UAbilityNode*> SubNodes;

	ACharacter* GetOwnerPawn();
};
