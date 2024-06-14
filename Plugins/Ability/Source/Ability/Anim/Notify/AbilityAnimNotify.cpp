// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityAnimNotify.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
FString UAbilityAnimNotify::GetNotifyName_Implementation() const
{
	return Name.ToString();
}

void UAbilityAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp->GetOwner())
	{
		NotifyDelegate.Broadcast(GetNotifyName_Implementation());
	}
}