// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Moba/Logic/MobaEnum.h"

#include "Animation/AnimNodeReference.h"
#include "Node/MobaAnimNode_base.h"
struct FAnimUpdateContext;
struct FAnimNodeReference;
struct FBlendSpacePlayerReference;
class APawn;
class UMobaAnimInstance;

//USTRUCT()
struct FStateMachine : public TSharedFromThis<FStateMachine>
{
	//GENERATED_USTRUCT_BODY()
	UMobaAnimInstance* MobaAnimInstance;
	class APawn* Onwer;
	ECharacterType::Type StateType;
	FAnimNodeReference AnimNodeReference;

	//Slot_Result
	virtual void EnterState(FAnimUpdateContext& UpdateContext, FAnimNodeReference& Node);
	virtual void BlendedInState(FAnimUpdateContext& UpdateContext, FAnimNodeReference& Node) {};
	virtual void ExitState(FAnimUpdateContext& UpdateContext, FAnimNodeReference& Node) {};
	virtual void BlendedOutState(FAnimUpdateContext& UpdateContext, FAnimNodeReference& Node) {};

	//MobaAnimInstanceProxy
	virtual void PostUpdate(UMobaAnimInstance* InAnimInstance) {};
	virtual void PreUpdate(UMobaAnimInstance* InAnimInstance, float DeltaSeconds) {};

	//Slot
	virtual void InitialUpdate(FAnimUpdateContext& UpdateContext, FAnimNodeReference& Node);
	virtual void Update(FAnimUpdateContext& UpdateContext, FAnimNodeReference& Node) {};
	virtual void BecomeRelevant(FAnimUpdateContext& UpdateContext, FAnimNodeReference& Node);

	//UpdateAnmationAsset
	virtual void UpdateAsset();

	FStateMachine(UMobaAnimInstance* InMobaAnimInstance, APawn* InOnwer) : MobaAnimInstance(InMobaAnimInstance), Onwer(InOnwer) {};
	virtual ~FStateMachine()
	{
		MobaAnimInstance = nullptr;
		Onwer = nullptr;
	};

};