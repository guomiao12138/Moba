// Fill out your copyright notice in the Description page of Project Settings.


#include "UAbilityNode_Root.h"

UAbilityNode_Root::UAbilityNode_Root()
{
}
#if WITH_EDITOR
void UAbilityNode_Root::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, TEXT("exec"), TEXT("then"));
}

FLinearColor UAbilityNode_Root::GetNodeTitleColor() const
{
	return FLinearColor::Red;
}

FText UAbilityNode_Root::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString("Root");
}

UEdGraphPin* UAbilityNode_Root::GetThenPin()
{
	return FindPinChecked(TEXT("then"));
}

void UAbilityNode_Root::CreateParamsPins()
{
}
#endif