// Fill out your copyright notice in the Description page of Project Settings.


#include "State_WalkRun.h"
#include "MobaAnimInstance.h"
//Engine
#include "Runtime/AnimGraphRuntime/Public/BlendSpacePlayerLibrary.h"
//Engine


void FState_WalkRun::PreUpdate(UMobaAnimInstance* InAnimInstance, float DeltaSeconds)
{
	if (InAnimInstance)
	{
		if (InAnimInstance->GetSpeed() <= 0.f)
		{
			InAnimInstance->SetChangeState(ECharacterType::Idle);
		}
	}
}

void FState_WalkRun::Update(FAnimUpdateContext& UpdateContext, FAnimNodeReference& Node)
{
	if (MobaAnimInstance)
	{
		FBlendSpacePlayerReference BlendSpacePlayerReference;
		bool Result;
		UBlendSpacePlayerLibrary::ConvertToBlendSpacePlayerPure(Node, BlendSpacePlayerReference, Result);
		if (Result)
		{
			if (FMobaAnimNode_BlendSpace* NodePtr = Node.GetAnimNodePtr<FMobaAnimNode_BlendSpace>())
			{
				NodePtr->SetPosition(FVector(0.f, MobaAnimInstance->GetSpeed(), 0.f));
			}
		}
	}
}
