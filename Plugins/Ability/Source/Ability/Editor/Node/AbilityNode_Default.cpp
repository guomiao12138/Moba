// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityNode_Default.h"

UAbilityNode_Default::UAbilityNode_Default()
{
}

void UAbilityNode_Default::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
}

FLinearColor UAbilityNode_Default::GetNodeTitleColor() const
{
	return FLinearColor::Red;
}