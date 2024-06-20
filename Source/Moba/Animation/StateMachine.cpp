// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine.h"
#include "Animation/AnimNodeReference.h"
#include "Runtime/AnimGraphRuntime/Public/SequencePlayerLibrary.h"
#include "Moba/DataAsset/CharacterAnimConfig.h"
#include "Runtime/AnimGraphRuntime/Public/BlendSpacePlayerLibrary.h"
#include "MobaAnimInstance.h"

void FStateMachine::PreUpdate(UMobaAnimInstance* InAnimInstance, float DeltaSeconds)
{

}

void FStateMachine::InitialUpdate(FAnimUpdateContext& UpdateContext, FAnimNodeReference& Node)
{
	if (FAnimationUpdateContext* AnimationUpdateContext = UpdateContext.GetContext())
	{
		MobaAnimInstance = Cast<UMobaAnimInstance>(AnimationUpdateContext->GetAnimInstanceObject());
	}
	else
	{
		return;
	}
	Onwer = MobaAnimInstance->TryGetPawnOwner();

	if (MobaAnimInstance && !MobaAnimInstance->AnimConfig)
	{
		UE_LOG(LogTemp, Warning, TEXT("AnimConfig [%d] : NULL"), __LINE__);
		return;
	}


	FName state;
	MobaAnimInstance->GetStateBySlot(Node, state);
	if (!MobaAnimInstance->StateMachineMap.Contains(state))
	{
		UE_LOG(LogTemp, Warning, TEXT("StateMachineMap [%d] : have not %s"), __LINE__, *MobaAnimInstance->CurrentState.ToString());
		return;
	}
	auto AnimAsset = MobaAnimInstance->AnimConfig->AnimConfig[MobaAnimInstance->StateMachineMap[state].StateType].AnimAsset;

	if (auto Asset = Cast<UAnimSequenceBase>(AnimAsset.TryLoad()))
	{
		FSequencePlayerReference SequencePlayerReference;
		bool Result;
		USequencePlayerLibrary::ConvertToSequencePlayerPure(Node, SequencePlayerReference, Result);

		if (Result)
		{
			Asset->bLoop = true;
			USequencePlayerLibrary::SetSequence(SequencePlayerReference, Asset);
		}
	}
	else if (auto BlendSpace = Cast<UBlendSpace>(AnimAsset.TryLoad()))
	{
		FBlendSpacePlayerReference BlendSpacePlayerReference;
		bool Result;
		UBlendSpacePlayerLibrary::ConvertToBlendSpacePlayerPure(Node, BlendSpacePlayerReference, Result);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("StateMachine InitialUpdate [%d] : AnimAsset Cast Faild"), __LINE__);
	}
}

void FStateMachine::Update(FAnimUpdateContext& UpdateContext, FAnimNodeReference& Node)
{
	FBlendSpacePlayerReference BlendSpacePlayerReference;
	bool Result;
	UBlendSpacePlayerLibrary::ConvertToBlendSpacePlayerPure(Node, BlendSpacePlayerReference, Result);
	if (Result)
	{
		UBlendSpacePlayerLibrary::SnapToPosition(BlendSpacePlayerReference, FVector(0.f, MobaAnimInstance->GetSpeed(), 0.f));
	}
}

void FStateMachine::BecomeRelevant(UMobaAnimInstance* InAnimInstance)
{

};

//void FState_WalkRun::PostUpdate(UMobaAnimInstance* MobaAnimInstance)
//{
//}
//
//void FState_WalkRun::InitialUpdate(FAnimUpdateContext& UpdateContext, FAnimNodeReference& Node)
//{
//
//}
//
//void FState_WalkRun::Update(FAnimUpdateContext& UpdateContext, FAnimNodeReference& Node)
//{
//}
//
//FState_WalkRun::~FState_WalkRun()
//{
//}
