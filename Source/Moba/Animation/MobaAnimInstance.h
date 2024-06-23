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
private:
	ECharacterType::Type CurrentState = ECharacterType::None;
	ECharacterType::Type BlendedInState = ECharacterType::None;
	ECharacterType::Type BlendedOutState = ECharacterType::None;

	ECharacterType::Type ChangeState = ECharacterType::None;
public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCharacterAnimConfig> AnimConfig;


	//AnimBlueprint StateResult Bind Function
	UFUNCTION(BlueprintCallable, Category = "MobaAnimInstance", meta = (BlueprintThreadSafe))
	void OnInitialUpdateByStateResult(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node);

	UFUNCTION(BlueprintCallable, Category = "MobaAnimInstance", meta = (BlueprintThreadSafe))
	void OnStateEntryByStateResult(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node);

	UFUNCTION(BlueprintCallable, Category = "MobaAnimInstance", meta = (BlueprintThreadSafe))
	void OnStateFullyBlendedInByStateResult(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node);

	UFUNCTION(BlueprintCallable, Category = "MobaAnimInstance", meta = (BlueprintThreadSafe))
	void OnStateExitByStateResult(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node);

	UFUNCTION(BlueprintCallable, Category = "MobaAnimInstance", meta = (BlueprintThreadSafe))
	void OnStateFullyBlendedOutByStateResult(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node);

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

	bool GetStateByMachine(FAnimNodeReference& Node, ECharacterType::Type& StateName);
	bool GetStateBySlot(FAnimNodeReference& Node, ECharacterType::Type& StateName);
	bool InGame();

	UFUNCTION(BlueprintPure, Category = "MobaAnimInstance", meta = (BlueprintThreadSafe))
	bool CheckChangeCharacterType(ECharacterType::Type Type);

	//AnimInstance
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;
	//AnimInstance

	float GetSpeed();
	void SetChangeState(ECharacterType::Type Type);
	void AddState(ECharacterType::Type Type, TSharedPtr<FStateMachine> State);
	TMap<ECharacterType::Type, TSharedPtr<FStateMachine>> StateMachineMap;

	friend FMobaAnimInstanceProxy;
};

