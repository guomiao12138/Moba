// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityEdGraphNodeBase.h"

void UMobaAbilityEdGraphNodeBase::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);

	CreatePin(EGPD_Input, TEXT("GraphNodePinCategory"), TEXT("GraphNodePinSubCategory"), nullptr, TEXT("AAAA"));
	CreatePin(EGPD_Output, TEXT("GraphNodePinCategory"), TEXT("GraphNodePinSubCategory"), nullptr, TEXT("BBBB"));
}

FText UMobaAbilityEdGraphNodeBase::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return NSLOCTEXT("Editor", "MobaAbility", "Begin");
}

FLinearColor UMobaAbilityEdGraphNodeBase::GetNodeTitleColor() const
{
	return FLinearColor::White;
}

FText UMobaAbilityEdGraphNodeBase::GetTooltipText() const
{
	return NSLOCTEXT("EditorExtenstion", "MobaAbility Graph Node Tooltip", "Tooltip");
}

//FSlateIcon UMobaAbilityEdGraphNodeBase::GetIconAndTint(FLinearColor& OutColor) const
//{
//	OutColor = GetNodeTitleColor();
//	static FSlateIcon Icon(FAppStyle::GetAppStyleSetName(), "Kismet.AllClasses.FunctionIcon");
//	return Icon;
//}
