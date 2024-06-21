// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine.h"
#include "Moba/DataAsset/CharacterAnimConfig.h"
#include "MobaAnimInstance.h"
//Engine
#include "Runtime/AnimGraphRuntime/Public/SequencePlayerLibrary.h"
#include "Runtime/AnimGraphRuntime/Public/BlendSpacePlayerLibrary.h"
//Engine

void FStateMachine::EnterState(FAnimUpdateContext& UpdateContext, FAnimNodeReference& Node)
{
}

void FStateMachine::InitialUpdate(FAnimUpdateContext& UpdateContext, FAnimNodeReference& Node)
{
	AnimNodeReference = Node;
}

void FStateMachine::BecomeRelevant(FAnimUpdateContext& UpdateContext, FAnimNodeReference& Node)
{

}

void FStateMachine::UpdateAsset()
{
	if (!MobaAnimInstance->StateMachineMap.Contains(StateType))
	{
		UE_LOG(LogTemp, Warning, TEXT("StateMachineMap [%d] : have not %s"), __LINE__, *ECharacterType::GetName(StateType).ToString());
		return;
	}
	auto AnimAsset = MobaAnimInstance->AnimConfig->AnimConfig[StateType].AnimAsset;

	if (auto Asset = Cast<UAnimSequenceBase>(AnimAsset.TryLoad()))
	{
		FSequencePlayerReference SequencePlayerReference;
		bool Result;
		USequencePlayerLibrary::ConvertToSequencePlayerPure(AnimNodeReference, SequencePlayerReference, Result);

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
		UBlendSpacePlayerLibrary::ConvertToBlendSpacePlayerPure(AnimNodeReference, BlendSpacePlayerReference, Result);

		if (Result)
		{
			UBlendSpacePlayerLibrary::SetBlendSpace(BlendSpacePlayerReference, BlendSpace);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("StateMachine InitialUpdate [%d] : AnimAsset Cast Faild"), __LINE__);
	}
}
