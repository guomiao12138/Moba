// Fill out your copyright notice in the Description page of Project Settings.


#include "UAbilityNode_Root.h"

UAbilityNode_Root::UAbilityNode_Root()
{
}

void UAbilityNode_Root::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
}

FLinearColor UAbilityNode_Root::GetNodeTitleColor() const
{
	return FLinearColor::Red;
}

FText UAbilityNode_Root::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString("Root");
}
