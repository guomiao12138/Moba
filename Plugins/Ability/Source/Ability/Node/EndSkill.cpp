// Fill out your copyright notice in the Description page of Project Settings.


#include "EndSkill.h"
#include "GameFramework/Character.h"
#include "Ability/MobaAbilityComponent.h"

void UEndSkill::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, TEXT("exec"), TEXT("then"));
}

FText UEndSkill::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString("EndSkill");
}

void UEndSkill::OnActiveNode()
{
	auto com = Cast<ACharacter>(GetOwnerPawn())->FindComponentByClass(UMobaAbilityComponent::StaticClass());
	Cast<UMobaAbilityComponent>(com)->SetCurrentAbility(nullptr);
}

void UEndSkill::CreateParamsPins()
{
}
