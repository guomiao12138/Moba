// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Moba/Logic/MobaEnum.h"
#include "Node/MobaAnimNode_base.h"
#include "StateMachine.generated.h"


/**
 * 
 */
struct FAnimUpdateContext;
struct FAnimNodeReference;
struct FBlendSpacePlayerReference;

USTRUCT()
struct FStateMachine 
{
	GENERATED_USTRUCT_BODY()

	class APawn* Onwer;
	class UMobaAnimInstance* MobaAnimInstance;
	ECharacterType::Type StateType;
	FMobaAnimNode_base SlotNode;
	virtual void EnterState() {};
	virtual void BlendedInState() {};
	virtual void ExitState() {};
	virtual void BlendedOutState() {};

	virtual void PostUpdate(UMobaAnimInstance* InAnimInstance) {};
	virtual void PreUpdate(UMobaAnimInstance* InAnimInstance, float DeltaSeconds);

	virtual void InitialUpdate(FAnimUpdateContext& UpdateContext, FAnimNodeReference& Node);
	virtual void Update(FAnimUpdateContext& UpdateContext, FAnimNodeReference& Node);
	virtual void BecomeRelevant(UMobaAnimInstance* InAnimInstance);


	virtual ~FStateMachine()
	{
		MobaAnimInstance = nullptr;
		Onwer = nullptr;
	};
};

struct FState_WalkRun : public FStateMachine
{
public:

	//virtual void PostUpdate(UMobaAnimInstance* MobaAnimInstance) override;
	//virtual void PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds) override;
	//virtual void InitialUpdate(FAnimUpdateContext& UpdateContext, FAnimNodeReference& Node) override;

	//virtual void Update(FAnimUpdateContext& UpdateContext, FAnimNodeReference& Node) override;

	//virtual ~FState_WalkRun();
};
