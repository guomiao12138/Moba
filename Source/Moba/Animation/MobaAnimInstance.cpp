// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAnimInstance.h"
#include "Runtime/AnimGraphRuntime/Public/AnimationStateMachineLibrary.h"
#include "Runtime/AnimGraphRuntime/Public/SequencePlayerLibrary.h"
#include "Animation/AnimNodeReference.h"
#include "Animation/AnimNode_StateResult.h"
#include "Animation/AnimNode_StateMachine.h"
#include "Animation/AnimInstanceProxy.h"

#include "Moba/DataAsset/CharacterAnimConfig.h"

void UMobaAnimInstance::OnStateEntry(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (GetState(Node, CurrentState))
	{
		if (StateMachineMap.Contains(CurrentState))
		{
			StateMachineMap[CurrentState].EnterState();
		}
		else
		{
			FStateMachine StateMachine;
			//StateMachine.Type = ECharacterType::GetValueByName(CurrentState);
			StateMachineMap.Emplace(CurrentState, StateMachine);
			UE_LOG(LogTemp, Display, TEXT("StateName : %s"), *CurrentState.ToString());
		}
	}
}

void UMobaAnimInstance::OnStateFullyBlendedIn(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
}

void UMobaAnimInstance::OnStateExit(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	FName StateName;
	if (GetState(Node, StateName))
	{
		StateMachineMap[StateName].ExitState();
	}
}

void UMobaAnimInstance::OnStateFullyBlendedOut(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
}

void UMobaAnimInstance::OnInitialUpdate(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
}

void UMobaAnimInstance::OnBecomeRelevant(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
}

void UMobaAnimInstance::OnUpdate(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
}

void UMobaAnimInstance::OnSlotInitialUpdate(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	//if (const FAnimationUpdateContext* AnimationUpdateContext = UpdateContext.GetContext())
	//{
	//	IAnimClassInterface* AnimBlueprintClass = AnimationUpdateContext->GetAnimClass();

	//	// Previous node to an FAnimNode_StateResult is always its owning FAnimNode_StateMachine
	//	const int32 MachineIndex = AnimBlueprintClass->GetAnimNodeProperties().Num() - 1 - AnimationUpdateContext->GetPreviousNodeId();
	//	//const int32 StateIndex = StateResultNode.GetStateIndex();

	//	const FAnimInstanceProxy* AnimInstanceProxy = AnimationUpdateContext->AnimInstanceProxy;
	//	if (const FAnimNode_StateMachine* MachineInstance = AnimInstanceProxy->GetStateMachineInstance(MachineIndex))
	//	{
	//		const int32 CurrentStateIndex = MachineInstance->GetCurrentState();
	//	}
	//	GetCurrentStateName(MachineIndex);
	//}
	if (InGame())
	{
		FSequencePlayerReference SequencePlayerReference;
		bool Result;
		USequencePlayerLibrary::ConvertToSequencePlayerPure(Node, SequencePlayerReference, Result);
		if (Result && AnimConfig)
		{
			auto AnimAsset = AnimConfig->AnimConfig[StateMachineMap[CurrentState].StateType].AnimAsset;
			if (auto Asset = Cast<UAnimSequenceBase>(AnimAsset.TryLoad()))
			{
				Asset->bLoop = true;
				USequencePlayerLibrary::SetSequence(SequencePlayerReference, Asset);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("CurrentState [%d] : AnimAsset Load Faild"), __LINE__);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("OnSlotInitialUpdate [%d] : ConvertToSequencePlayerPure Faild"), __LINE__);
		}
	}


}

void UMobaAnimInstance::OnSlotBecomeRelevant(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{

}

void UMobaAnimInstance::OnSlotUpdate(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	FSequencePlayerReference SequencePlayerReference;
	bool Result;
	USequencePlayerLibrary::ConvertToSequencePlayerPure(Node, SequencePlayerReference, Result);
	if (Result)
	{
		USequencePlayerLibrary::SetSequence(SequencePlayerReference, nullptr);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OnSlotInitialUpdate [%d] : ConvertToSequencePlayerPure Faild"), __LINE__);
	}
}

bool UMobaAnimInstance::GetState(FAnimNodeReference& Node, FName& StateName)
{
	if (InGame())
	{
		FAnimNode_StateMachine* StateMachineNode = Node.GetAnimNodePtr<FAnimNode_StateMachine>();
		if (StateMachineNode)
		{
			StateName = StateMachineNode->GetStateInfo(StateMachineNode->GetCurrentState()).StateName;
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("GetState [%d] : StateMachineNode Is Null"), __LINE__);
			return false;
		}
	}

	return false;
}

bool UMobaAnimInstance::InGame()
{
	EWorldType::Type Type = GetWorld()->WorldType;
	if (Type == EWorldType::Game || Type == EWorldType::GameRPC || Type == EWorldType::PIE)
	{
		return true;
	}
	return false;
}

void UMobaAnimInstance::FStateMachine::EnterState()
{
}

void UMobaAnimInstance::FStateMachine::ExitState()
{
}
