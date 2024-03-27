// Fill out your copyright notice in the Description page of Project Settings.


#include "EndNode.h"
#include "GameFramework/Character.h"
#include "Ability/Runtime/MobaAbilityComponent.h"

void UEndNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
}

FText UEndNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString("EndSkill");
}

void UEndNode::OnActiveNode()
{
	auto com = Cast<ACharacter>(GetOwnerPawn())->FindComponentByClass(UMobaAbilityComponent::StaticClass());
	Cast<UMobaAbilityComponent>(com)->SetCurrentAbility(nullptr);
}

void UEndNode::CreateParamsPins()
{
}
