// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAnimInstance.h"
#include "State_WalkRun.h"
#include "State_Idle.h"
#include "State_Skill.h"
#include "Moba/Animation/Node/MobaAnimNode_base.h"
#include "Moba/DataAsset/CharacterAnimConfig.h"

//Engine
#include "Animation/AnimNodeReference.h"
#include "Animation/AnimNode_StateResult.h"
#include "Animation/AnimNode_StateMachine.h"
//Engine

void UMobaAnimInstance::OnInitialUpdateByStateResult(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (InGame())
	{
		//GetStateByMachine(Node, ChangeState);
	}
}

void UMobaAnimInstance::OnStateEntryByStateResult(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (InGame())
	{
		//NotGameThread
		ECharacterType::Type state = ECharacterType::None;
		if (GetStateByMachine(Node, state))
		{
			if (StateMachineMap.Contains(state))
			{
				StateMachineMap[state]->EnterState(UpdateContext, Node);
			}
		}
	}
}

void UMobaAnimInstance::OnStateFullyBlendedInByStateResult(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
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

void UMobaAnimInstance::OnStateExitByStateResult(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
{
	if (InGame())
	{
		//NotGameThread
		ECharacterType::Type state = ECharacterType::None;
		if (GetStateByMachine(Node, state))
		{
			if (StateMachineMap.Contains(state))
			{
				StateMachineMap[state]->ExitState(UpdateContext, Node);
			}
		}
	}
}

void UMobaAnimInstance::OnStateFullyBlendedOutByStateResult(UPARAM(ref)FAnimUpdateContext& UpdateContext, UPARAM(ref)FAnimNodeReference& Node)
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
		//Enter After
		if (const FAnimationUpdateContext* AnimationUpdateContext = UpdateContext.GetContext())
		{
			int InitialState = GetMachineDescription(IAnimClassInterface::GetFromClass(GetClass()), Node.GetAnimNodePtr<FAnimNode_StateMachine>())->InitialState;
			FName StateName = Node.GetAnimNodePtr<FAnimNode_StateMachine>()->GetStateInfo(InitialState).StateName;
			SetChangeState(ECharacterType::GetValueByName(StateName));
		}
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
		ECharacterType::Type state = ECharacterType::None;
		if (GetStateBySlot(Node, state))
		{
			if (StateMachineMap.Contains(state))
			{
				StateMachineMap[state]->BecomeRelevant(UpdateContext, Node);
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
		AnimConfig = FindObject<UCharacterAnimConfig>(this, TEXT("/Game/Anim.AnimDataAsset.AnimDataAsset"));

		if (!AnimConfig)
		{
			AnimConfig = LoadObject<UCharacterAnimConfig>(this, TEXT("/Game/Anim/AnimDataAsset.AnimDataAsset"));
		}

		for (int i = 0; i < ECharacterType::Max; i++)
		{
			ECharacterType::Type state = ECharacterType::Type(i);

			if (!StateMachineMap.Contains(state))
			{
				switch (state)
				{
				case ECharacterType::WalkRun:
					AddState(state, MakeShareable(new FState_WalkRun()));
					break;

				case ECharacterType::Idle:
					AddState(state, MakeShareable(new FState_Idle()));
					break;

				case ECharacterType::Skill:
					AddState(state, MakeShareable(new FState_Skill()));
					break;

				case ECharacterType::None:
					break;

				default:
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
				if (StateMachineMap[ChangeState]->UpdateAsset())
				{
					CurrentState = ChangeState;
				};
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

void UMobaAnimInstance::AddState(ECharacterType::Type Type, TSharedPtr<FStateMachine> State)
{
	State->StateType = Type;
	State->MobaAnimInstance = this;
	State->Onwer = TryGetPawnOwner();
	StateMachineMap.Emplace(Type, State);
}

void FMobaAnimInstanceProxy::PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds)
{
	//GameThread
	Super::PreUpdate(InAnimInstance, DeltaSeconds);

	if (auto inst = Cast<UMobaAnimInstance>(InAnimInstance))
	{
		if (inst->StateMachineMap.Contains(inst->CurrentState))
		{
			inst->StateMachineMap[inst->CurrentState]->PreUpdate(inst, DeltaSeconds);
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
		if (inst->StateMachineMap.Contains(inst->CurrentState))
		{
			inst->StateMachineMap[inst->CurrentState]->PostUpdate(inst);
		}
	}

}

void FMobaAnimInstanceProxy::UpdateAnimationNode(const FAnimationUpdateContext& InContext)
{
	//NotGameThread
	Super::UpdateAnimationNode(InContext);

}