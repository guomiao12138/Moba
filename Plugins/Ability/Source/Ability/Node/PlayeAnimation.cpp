// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayeAnimation.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimSequence.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraph.h"

void UPlayeAnimation::OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted)
{
}

void UPlayeAnimation::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
}

void UPlayeAnimation::OnActiveNode()
{
	//Super::OnActiveNode();
	if (!GetOwnerPawn())
	{
		return;
	}
	if (auto SkeletalMeshComponent = GetOwnerPawn()->FindComponentByClass<USkeletalMeshComponent>())
	{
		if (UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance())
		{
			AnimInstance->OnPlayMontageNotifyBegin.AddUniqueDynamic(this, &UPlayeAnimation::OnNotifyBeginReceived);
			AnimInstance->OnPlayMontageNotifyEnd.AddUniqueDynamic(this, &UPlayeAnimation::OnNotifyEndReceived);

			auto mon = AnimInstance->PlaySlotAnimationAsDynamicMontage(Asset, TEXT("Ability.Active"));

			BlendingOutDelegate.BindUObject(this, &UPlayeAnimation::OnMontageBlendingOut);
			AnimInstance->Montage_SetBlendingOutDelegate(BlendingOutDelegate, mon);

			MontageEndedDelegate.BindUObject(this, &UPlayeAnimation::OnMontageEnded);
			AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, mon);



		}

		//SkeletalMeshComponent->PlayAnimation(Asset, false);
	}
	else
	{
		UE_LOG(Ability, Error, TEXT("[%s] [%s] : Owner not SkeletalMeshComponent"), *Ability_LINE, GetFName());
	}
}

bool UPlayeAnimation::OnDeActiveNode()
{
	if (GetOwnerPawn())
	{
		if (auto SkeletalMeshComponent = GetOwnerPawn()->FindComponentByClass<USkeletalMeshComponent>())
		{
			if (UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance())
			{
				AnimInstance->OnPlayMontageNotifyBegin.Remove(this, TEXT("OnNotifyBeginReceived"));
				AnimInstance->OnPlayMontageNotifyEnd.Remove(this, TEXT("OnNotifyEndReceived"));
			}
			return true;
		}
	}
	return false;
}

bool UPlayeAnimation::IsNotifyValid(FName NotifyName)
{
	if(FindPinChecked(NotifyName))
	{
		return true;
	}
	return false;
}

void UPlayeAnimation::OnNotifyBeginReceived(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	if (IsNotifyValid(NotifyName))
	{
		OnNotifyBegin.Broadcast(NotifyName);
		if (auto Pin = FindPinChecked(NotifyName))
		{
			if (Pin->LinkedTo.IsValidIndex(0))
			{
				Cast<UAbilityNode>(Pin->LinkedTo[0]->GetOwningNode())->OnActiveNode();
			}
		}
	}
}

void UPlayeAnimation::OnNotifyEndReceived(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	if (IsNotifyValid(NotifyName))
	{
		OnNotifyEnd.Broadcast(NotifyName);
	}
}

void UPlayeAnimation::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	if (Asset)
	{
		for (auto Notify : Asset->Notifies)
		{
			CreatePin(EGPD_Output, TEXT("exec"), Notify.NotifyName);
		}
	}


}

void UPlayeAnimation::PinDefaultValueChanged(UEdGraphPin* Pin)
{
	ReconstructNode();
	UEdGraphPin* AssetPin = FindPinChecked(TEXT("Asset"));
	AssetPin->CopyPersistentDataFromOldPin(*Pin);

	Super::PinDefaultValueChanged(AssetPin);

	GetGraph()->NotifyNodeChanged(this);
}
