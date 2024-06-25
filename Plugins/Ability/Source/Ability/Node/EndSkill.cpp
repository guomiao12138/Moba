// Fill out your copyright notice in the Description page of Project Settings.


#include "EndSkill.h"
#include "GameFramework/Character.h"
#include "Ability/MobaAbilityComponent.h"

#if WITH_EDITOR
void UEndSkill::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, TEXT("exec"), TEXT("then"));
}

#endif
void UEndSkill::OnActiveNode()
{
	if (auto com = Cast<ACharacter>(GetOwnerPawn())->FindComponentByClass(UMobaAbilityComponent::StaticClass()))
	{
		Cast<UMobaAbilityComponent>(com)->SetCurrentAbility(nullptr);
	}
	
}