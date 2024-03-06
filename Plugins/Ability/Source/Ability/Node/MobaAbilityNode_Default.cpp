// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityNode_Default.h"

UMobaAbilityNode_Default::UMobaAbilityNode_Default()
{

}

void UMobaAbilityNode_Default::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
}

FLinearColor UMobaAbilityNode_Default::GetNodeTitleColor() const
{
	return FLinearColor::Red;
}