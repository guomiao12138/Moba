// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayeAnimation.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimMontage.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraph.h"
#include "Ability/Anim/Notify/AbilityAnimNotify.h"

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
			auto mon = AnimInstance->PlaySlotAnimationAsDynamicMontage(Asset, TEXT("Active"));
			mon->SyncGroup = TEXT("Ability");
		}

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

void UPlayeAnimation::PostLoad()
{
	Super::PostLoad();
	if (Asset)
	{
		for (auto Notify : Asset->Notifies)
		{
			Cast<UAbilityAnimNotify>(Notify.Notify)->NotifyDelegate.AddUObject(this, &UPlayeAnimation::Notify);
		}
	}
}

bool UPlayeAnimation::IsNotifyValid(FName NotifyName)
{
	if(FindPinChecked(NotifyName))
	{
		return true;
	}
	return false;
}

void UPlayeAnimation::Notify(FString NotifyName)
{
	if (IsNotifyValid(*NotifyName))
	{
		if (auto Pin = FindPinChecked(NotifyName))
		{
			if (Pin->LinkedTo.IsValidIndex(0))
			{
				Cast<UAbilityNode>(Pin->LinkedTo[0]->GetOwningNode())->OnActiveNode();
			}
		}
	}
}

void UPlayeAnimation::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	if (Asset)
	{
		for (auto Notify : Asset->Notifies)
		{
			Cast<UAbilityAnimNotify>(Notify.Notify)->NotifyDelegate.AddUObject(this, &UPlayeAnimation::Notify);
			CreatePin(EGPD_Output, TEXT("exec"), *Notify.Notify->GetNotifyName());
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
