// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAnimInstance.h"
#include "State_WalkRun.h"
#include "State_Idle.h"
#include "State_Skill.h"
#include "Moba/Animation/Node/MobaAnimNode_base.h"
//Engine
#include "Animation/AnimNodeReference.h"
#include "Animation/AnimNode_StateResult.h"
#include "Animation/AnimNode_StateMachine.h"
//Engine


void UMobaAnimInstance::OnStateEntry(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (InGame())
	{
		//NotGameThread
		ECharacterType::Type state = ECharacterType::None;
		if (StateMachineMap.Contains(state))
		{
			StateMachineMap[state]->EnterState(UpdateContext, Node);
		}
	}
}

void UMobaAnimInstance::OnStateFullyBlendedIn(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (InGame())
	{
		//NotGameThread
		if (GetStateByMachine(Node, BlendedInState))
		{
			if (StateMachineMap.Contains(BlendedOutState))
			{
				StateMachineMap[BlendedOutState]->BlendedInState(UpdateContext, Node);
			}
		}
	}
}

void UMobaAnimInstance::OnStateExit(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (InGame())
	{
		//NotGameThread
		ECharacterType::Type state = ECharacterType::None;
		if (StateMachineMap.Contains(state))
		{
			StateMachineMap[state]->ExitState(UpdateContext, Node);
		}
	}
}

void UMobaAnimInstance::OnStateFullyBlendedOut(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (InGame())
	{
		//NotGameThread
		if (GetStateByMachine(Node, BlendedOutState))
		{
			if (StateMachineMap.Contains(BlendedOutState))
			{
				StateMachineMap[BlendedOutState]->BlendedOutState(UpdateContext, Node);
			}
		}
	}
}

void UMobaAnimInstance::OnInitialUpdateByMachine(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (InGame())
	{

	}
}

void UMobaAnimInstance::OnBecomeRelevantByMachine(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (InGame())
	{
		//NotGameThread
	}
}

void UMobaAnimInstance::OnUpdateByMachine(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (InGame())
	{
		//NotGameThread
	}
}

void UMobaAnimInstance::OnSlotInitialUpdate(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (InGame())
	{
		//NotGameThread
		ECharacterType::Type state = ECharacterType::None;
		if (GetStateBySlot(Node, state))
		{
			if (StateMachineMap.Contains(state))
			{
				StateMachineMap[state]->InitialUpdate(UpdateContext, Node);
			}
		}
	}
}

void UMobaAnimInstance::OnSlotBecomeRelevant(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (InGame())
	{
		//NotGameThread
		if (GetStateBySlot(Node, CurrentState))
		{
			if (StateMachineMap.Contains(CurrentState))
			{
				StateMachineMap[CurrentState]->BecomeRelevant(UpdateContext, Node);
			}
		}
	}
}

void UMobaAnimInstance::OnSlotUpdate(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (InGame())
	{
		//NotGameThread
		ECharacterType::Type state = ECharacterType::None;
		if (GetStateBySlot(Node, state))
		{
			if (StateMachineMap.Contains(state))
			{
				StateMachineMap[state]->Update(UpdateContext, Node);
			}
		}
	}
}

bool UMobaAnimInstance::GetStateByMachine(FAnimNodeReference& Node, ECharacterType::Type& StateName)
{
	if (InGame())
	{
		FAnimNode_StateMachine* StateMachineNode = Node.GetAnimNodePtr<FAnimNode_StateMachine>();
		if (StateMachineNode)
		{
			StateName = ECharacterType::GetValueByName(StateMachineNode->GetStateInfo(StateMachineNode->GetCurrentState()).StateName);
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

bool UMobaAnimInstance::GetStateBySlot(FAnimNodeReference& Node, ECharacterType::Type& StateName)
{
	if (InGame())
	{
		if (FMobaAnimNode_Sequence* SequenceNode = Node.GetAnimNodePtr<FMobaAnimNode_Sequence>())
		{
			StateName = SequenceNode->SlotName;
			return true;
		}
		else if (FMobaAnimNode_BlendSpace* BlendSpacNode = Node.GetAnimNodePtr<FMobaAnimNode_BlendSpace>())
		{
			StateName = BlendSpacNode->SlotName;
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("GetStateBySlot [%d] : AnimNode Is Null"), __LINE__);
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

bool UMobaAnimInstance::CheckChangeCharacterType(ECharacterType::Type Type)
{
	if (ChangeState == Type)
	{
		return true;
	}
	return false;
}

void UMobaAnimInstance::NativeInitializeAnimation()
{
	if (InGame())
	{
		for (int i = 0; i < ECharacterType::Max; i++)
		{
			ECharacterType::Type state = ECharacterType::Type(i);

			if (!StateMachineMap.Contains(state))
			{
				switch (state)
				{
				case ECharacterType::WalkRun:
				{
					TSharedPtr<FState_WalkRun> State_WalkRun = MakeShareable(new FState_WalkRun(this, TryGetPawnOwner()));
					State_WalkRun->StateType = state;
					StateMachineMap.Emplace(state, State_WalkRun);
				}
				break;
				case ECharacterType::Idle:
				{
					TSharedPtr<FState_Idle> State_Idle = MakeShareable(new FState_Idle(this, TryGetPawnOwner()));
					State_Idle->StateType = state;
					StateMachineMap.Emplace(state, State_Idle);
				}
				break;
				case ECharacterType::Skill:
				{
					TSharedPtr<FState_Skill> State_Idle = MakeShareable(new FState_Skill(this, TryGetPawnOwner()));
					State_Idle->StateType = state;
					StateMachineMap.Emplace(state, State_Idle);
				}
				case ECharacterType::None:
					break;
				default:
					TSharedPtr<FStateMachine> State_WalkRun = MakeShareable(new FStateMachine(this, TryGetPawnOwner()));
					State_WalkRun->StateType = state;
					StateMachineMap.Emplace(state, State_WalkRun);
					break;
				}
			}
		}
	}
}

void UMobaAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (InGame())
	{
		if (ChangeState != CurrentState)
		{
			if (StateMachineMap.Contains(ChangeState))
			{
				StateMachineMap[ChangeState]->UpdateAsset();
			}
		}
	}
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

void UMobaAnimInstance::SetChangeState(ECharacterType::Type Type)
{
	ChangeState = Type;
}

void FMobaAnimInstanceProxy::PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds)
{
	//GameThread
	Super::PreUpdate(InAnimInstance, DeltaSeconds);

	if (auto inst = Cast<UMobaAnimInstance>(InAnimInstance))
	{
		for (auto kv : inst->StateMachineMap)
		{
			kv.Value->PreUpdate(inst, DeltaSeconds);
		}
	}
}

void FMobaAnimInstanceProxy::Update(float DeltaSeconds)
{
	//NotGameThread
	Super::Update(DeltaSeconds);


}


void FMobaAnimInstanceProxy::PostUpdate(UAnimInstance* InAnimInstance) const
{
	//GameThread
	Super::PostUpdate(InAnimInstance);

	if (auto inst = Cast<UMobaAnimInstance>(InAnimInstance))
	{
		for (auto kv : inst->StateMachineMap)
		{
			kv.Value->PostUpdate(inst);
		}
	}

}

void FMobaAnimInstanceProxy::UpdateAnimationNode(const FAnimationUpdateContext& InContext)
{
	//NotGameThread
	Super::UpdateAnimationNode(InContext);

}