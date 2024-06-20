// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimExecutionContext.h"
#include "Moba/Logic/MobaEnum.h"
#include "Moba/Animation/StateMachine.h"
#include "Animation/AnimInstanceProxy.h"
#include "MobaAnimInstance.generated.h"

/**
 * 
 */

struct FAnimUpdateContext;
struct FStateMachine;
USTRUCT()
struct FMobaAnimInstanceProxy : public FAnimInstanceProxy
{
	GENERATED_USTRUCT_BODY()

	FMobaAnimInstanceProxy() {};
	FMobaAnimInstanceProxy(UAnimInstance* Instance) : FAnimInstanceProxy(Instance) {};

	virtual void UpdateAnimationNode(const FAnimationUpdateContext& InContext) override;
	virtual void PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds) override;
	virtual void Update(float DeltaSeconds) override;
	virtual void PostUpdate(UAnimInstance* InAnimInstance) const override;
};

UCLASS()
class MOBA_API UMobaAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCharacterAnimConfig> AnimConfig;
	FName CurrentState;
	FName BlendedInState;
	FName BlendedOutState;

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
	void OnInitialUpdateByMachine(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node);

	UFUNCTION(BlueprintCallable, Category = "MobaAnimInstance", meta = (BlueprintThreadSafe))
	void OnBecomeRelevantByMachine(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node);

	UFUNCTION(BlueprintCallable, Category = "MobaAnimInstance", meta = (BlueprintThreadSafe))
	void OnUpdateByMachine(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node);
	
	//Slot
	UFUNCTION(BlueprintCallable, Category = "MobaAnimInstance", meta = (BlueprintThreadSafe))
	void OnSlotInitialUpdate(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node);

	UFUNCTION(BlueprintCallable, Category = "MobaAnimInstance", meta = (BlueprintThreadSafe))
	void OnSlotBecomeRelevant(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node);

	UFUNCTION(BlueprintCallable, Category = "MobaAnimInstance", meta = (BlueprintThreadSafe))
	void OnSlotUpdate(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node);

	bool GetStateByMachine(FAnimNodeReference& Node, FName& StateName);
	bool GetStateBySlot(FAnimNodeReference& Node, FName& StateName);
	bool InGame();


	//AnimInstance
	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;
	//AnimInstance

	float GetSpeed();
	TMap<FName, struct FStateMachine> StateMachineMap;

};

