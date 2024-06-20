// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAnimInstance.h"
#include "Runtime/AnimGraphRuntime/Public/AnimationStateMachineLibrary.h"
#include "Animation/AnimNodeReference.h"
#include "Animation/AnimNode_StateResult.h"
#include "Animation/AnimNode_StateMachine.h"
#include "Moba/Animation/Node/MobaAnimNode_base.h"


void UMobaAnimInstance::OnStateEntry(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (GetStateByMachine(Node, CurrentState))
	{
		if (StateMachineMap.Contains(CurrentState))
		{
			StateMachineMap[CurrentState].EnterState();
		}
	}
}

void UMobaAnimInstance::OnStateFullyBlendedIn(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (GetStateByMachine(Node, BlendedInState))
	{
		if (StateMachineMap.Contains(BlendedOutState))
		{
			//FAnimationStateResultReference AnimationStateResultReference;
			//bool Result;
			//UAnimationStateMachineLibrary::ConvertToAnimationStateResultPure(Node, AnimationStateResultReference, Result);
			//float time = UAnimationStateMachineLibrary::GetRelevantAnimTimeRemaining(UpdateContext, AnimationStateResultReference);
			StateMachineMap[BlendedOutState].BlendedInState();
		}
	}
}

void UMobaAnimInstance::OnStateExit(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (GetStateByMachine(Node, CurrentState))
	{
		if (StateMachineMap.Contains(CurrentState))
		{
			StateMachineMap[CurrentState].ExitState();
		}
	}
}

void UMobaAnimInstance::OnStateFullyBlendedOut(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (GetStateByMachine(Node, BlendedOutState))
	{
		if (StateMachineMap.Contains(BlendedOutState))
		{
			StateMachineMap[BlendedOutState].BlendedOutState();
		}
	}
}

void UMobaAnimInstance::OnInitialUpdateByMachine(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (InGame())
	{
		FAnimNode_StateMachine* StateMachineNode = Node.GetAnimNodePtr<FAnimNode_StateMachine>();
		for (int i = 0; i < ECharacterType::Max; i++)
		{
			FName state = ECharacterType::GetName(ECharacterType::Type(i));

			if (!StateMachineMap.Contains(state))
			{
				switch (ECharacterType::Type(i))
				{
				case ECharacterType::WalkRun:
					//{
					//	FState_WalkRun State_WalkRun;
					//	State_WalkRun.StateType = ECharacterType::Type(i);
					//	StateMachineMap.Emplace(state, State_WalkRun);
					//}
					//break;
				default:
					FStateMachine StateMachine;
					StateMachine.StateType = ECharacterType::Type(i);
					StateMachineMap.Emplace(state, StateMachine);
					break;
				}


			}
		}
	}
}

void UMobaAnimInstance::OnBecomeRelevantByMachine(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (InGame())
	{

	}
}

void UMobaAnimInstance::OnUpdateByMachine(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (InGame())
	{

	}
}

void UMobaAnimInstance::OnSlotInitialUpdate(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (InGame())
	{
		FName state;
		if (GetStateBySlot(Node, state))
		{
			if (StateMachineMap.Contains(state))
			{
				StateMachineMap[state].InitialUpdate(UpdateContext, Node);
			}
		}
	}
}

void UMobaAnimInstance::OnSlotBecomeRelevant(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (InGame())
	{
		FName state;
		if (GetStateBySlot(Node, state))
		{
			if (StateMachineMap.Contains(state))
			{
				StateMachineMap[state].BecomeRelevant(this);
			}
		}
	}
}

void UMobaAnimInstance::OnSlotUpdate(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (InGame())
	{
		FName state;
		if (GetStateBySlot(Node, state))
		{
			if (StateMachineMap.Contains(state))
			{
				StateMachineMap[state].Update(UpdateContext, Node);
			}
		}
	}
}

bool UMobaAnimInstance::GetStateByMachine(FAnimNodeReference& Node, FName& StateName)
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
			UE_LOG(LogTemp, Warning, TEXT("GetStateByMachine [%d] : StateMachineNode Is Null"), __LINE__);
			return false;
		}
	}

	return false;
}

bool UMobaAnimInstance::GetStateBySlot(FAnimNodeReference& Node, FName& StateName)
{
	if (InGame())
	{
		FMobaAnimNode_base* StateMachineNode = Node.GetAnimNodePtr<FMobaAnimNode_base>();
		if (StateMachineNode)
		{
			StateName = ECharacterType::GetName(StateMachineNode->SlotName);
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("GetStateByMachine [%d] : StateMachineNode Is Null"), __LINE__);
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

FAnimInstanceProxy* UMobaAnimInstance::CreateAnimInstanceProxy()
{
	return new FMobaAnimInstanceProxy(this);
}

float UMobaAnimInstance::GetSpeed()
{
	if (auto pawn = TryGetPawnOwner())
	{
		if (auto MovementComponent = pawn->FindComponentByClass<UCharacterMovementComponent>())
		{
			return MovementComponent->Velocity.Length();
		}
	}
	return 0.f;
}

void FMobaAnimInstanceProxy::PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds)
{
	Super::PreUpdate(InAnimInstance, DeltaSeconds);

	if (auto inst = Cast<UMobaAnimInstance>(InAnimInstance))
	{
		for (auto kv : inst->StateMachineMap)
		{
			kv.Value.PreUpdate(inst, DeltaSeconds);
		}
	}
}

void FMobaAnimInstanceProxy::Update(float DeltaSeconds)
{
	Super::Update(DeltaSeconds);

}


void FMobaAnimInstanceProxy::PostUpdate(UAnimInstance* InAnimInstance) const
{
	Super::PostUpdate(InAnimInstance);

	if (auto inst = Cast<UMobaAnimInstance>(InAnimInstance))
	{
		for (auto kv : inst->StateMachineMap)
		{
			kv.Value.PostUpdate(inst);
		}
	}

}

void FMobaAnimInstanceProxy::UpdateAnimationNode(const FAnimationUpdateContext& InContext)
{

	Super::UpdateAnimationNode(InContext);

}