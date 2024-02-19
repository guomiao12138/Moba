// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityEdGraphNodeBase.h"

void UMobaAbilityEdGraphNodeBase::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, TEXT("GraphNodePinCategory"), TEXT("GraphNodePinSubCategory"), nullptr, TEXT(""));
}

FText UMobaAbilityEdGraphNodeBase::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return NSLOCTEXT("Editor", "MobaAbility", "Begin");
}

FLinearColor UMobaAbilityEdGraphNodeBase::GetNodeTitleColor() const
{
	return FLinearColor::Red;
}

FText UMobaAbilityEdGraphNodeBase::GetTooltipText() const
{
	return NSLOCTEXT("EditorExtenstion", "MobaAbility Graph Node Tooltip", "Tooltip");
}

FSlateIcon UMobaAbilityEdGraphNodeBase::GetIconAndTint(FLinearColor& OutColor) const
{
	OutColor = FLinearColor::Red;
	return FSlateIcon(FAppStyle::GetAppStyleSetName(), "ClassIcon.BlendSpace");
}
