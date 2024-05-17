// Fill out your copyright notice in the Description page of Project Settings.


#include "Root.h"

URoot::URoot()
{
}
#if WITH_EDITOR
void URoot::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, TEXT("exec"), TEXT("then"));
}

FLinearColor URoot::GetNodeTitleColor() const
{
	return FLinearColor::Red;
}

UEdGraphPin* URoot::GetThenPin()
{
	return FindPinChecked(TEXT("then"));
}

#endif