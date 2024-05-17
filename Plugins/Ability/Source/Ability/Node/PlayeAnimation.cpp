// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayeAnimation.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimSequence.h"

void UPlayeAnimation::OnActiveNode()
{
	if (auto com = GetOwnerPawn()->FindComponentByClass<USkeletalMeshComponent>())
	{
		com->PlayAnimation(Asset, false);
	}
	else
	{
		UE_LOG(Ability, Error, TEXT("[%s] [%s] : Owner not SkeletalMeshComponent"), *Ability_LINE, GetFName());
	}
}

bool UPlayeAnimation::OnDeActiveNode()
{
	return false;
}

void UPlayeAnimation::CreateParamsPins()
{
	Super::CreateParamsPins();

	if (Asset)
	{
		for (auto notify : Asset->Notifies)
		{
			CreatePin(EGPD_Output, TEXT("exec"), notify.NotifyName);
		}
	}

}
