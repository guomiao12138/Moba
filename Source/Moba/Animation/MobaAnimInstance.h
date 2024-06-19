// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimExecutionContext.h"
#include "MobaAnimInstance.generated.h"

/**
 * 
 */

struct FAnimUpdateContext;
UCLASS()
class MOBA_API UMobaAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	


public:




	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCharacterAnimConfig> AnimConfig;
	FName CurrentState;

	//AnimBlueprint State Bind Function
	UFUNCTION(BlueprintCallable, Category = "MobaAnimInstance", meta = (BlueprintThreadSafe))
	void OnStateEntry(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node);

	UFUNCTION(BlueprintCallable, Category = "MobaAnimInstance", meta = (BlueprintThreadSafe))
	void OnStateFullyBlendedIn(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node);

	UFUNCTION(BlueprintCallable, Category = "MobaAnimInstance", meta = (BlueprintThreadSafe))
	void OnStateExit(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node);

	UFUNCTION(BlueprintCallable, Category = "MobaAnimInstance", meta = (BlueprintThreadSafe))
	void OnStateFullyBlendedOut(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node);

	//Machine
	UFUNCTION(BlueprintCallable, Category = "MobaAnimInstance", meta = (BlueprintThreadSafe))
	void OnInitialUpdate(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node);

	UFUNCTION(BlueprintCallable, Category = "MobaAnimInstance", meta = (BlueprintThreadSafe))
	void OnBecomeRelevant(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node);

	UFUNCTION(BlueprintCallable, Category = "MobaAnimInstance", meta = (BlueprintThreadSafe))
	void OnUpdate(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node);	
	
	//Slot
	UFUNCTION(BlueprintCallable, Category = "MobaAnimInstance", meta = (BlueprintThreadSafe))
	void OnSlotInitialUpdate(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node);

	UFUNCTION(BlueprintCallable, Category = "MobaAnimInstance", meta = (BlueprintThreadSafe))
	void OnSlotBecomeRelevant(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node);

	UFUNCTION(BlueprintCallable, Category = "MobaAnimInstance", meta = (BlueprintThreadSafe))
	void OnSlotUpdate(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node);

	bool GetState(FAnimNodeReference& Node, FName& StateName);

	struct FStateMachine {
		EInputAction::Type State;

		void EnterState();
		void ExitState();
	};

	TMap<FName, FStateMachine> StateMachineMap;


	bool InGame();
};
