// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityEdGraphNodeBase.h"

void UMobaAbilityEdGraphNodeBase::AllocateDefaultPins()
{
<<<<<<< HEAD
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);

	CreatePin(EGPD_Input, TEXT("GraphNodePinCategory"), TEXT("GraphNodePinSubCategory"), nullptr, TEXT("AAAA"));
	CreatePin(EGPD_Output, TEXT("GraphNodePinCategory"), TEXT("GraphNodePinSubCategory"), nullptr, TEXT("BBBB"));
=======
	CreatePin(EGPD_Input, TEXT("GraphNodePinCategory"), TEXT("GraphNodePinSubCategory"), nullptr, TEXT(""));
	//CreatePin(EGPD_Output, TEXT("GraphNodePinCategory"), TEXT("GraphNodePinSubCategory"), nullptr, TEXT(""));
>>>>>>> 595b50cfd57cee54cfddcf2bb92eddc25d608d11
}

FText UMobaAbilityEdGraphNodeBase::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return NSLOCTEXT("Editor", "MobaAbility", "Begin");
}

FLinearColor UMobaAbilityEdGraphNodeBase::GetNodeTitleColor() const
{
<<<<<<< HEAD
	return FLinearColor::White;
=======
	return FLinearColor::Red;
>>>>>>> 595b50cfd57cee54cfddcf2bb92eddc25d608d11
}

FText UMobaAbilityEdGraphNodeBase::GetTooltipText() const
{
	return NSLOCTEXT("EditorExtenstion", "MobaAbility Graph Node Tooltip", "Tooltip");
}

<<<<<<< HEAD
//FSlateIcon UMobaAbilityEdGraphNodeBase::GetIconAndTint(FLinearColor& OutColor) const
//{
//	OutColor = GetNodeTitleColor();
//	static FSlateIcon Icon(FAppStyle::GetAppStyleSetName(), "Kismet.AllClasses.FunctionIcon");
//	return Icon;
//}
=======
FSlateIcon UMobaAbilityEdGraphNodeBase::GetIconAndTint(FLinearColor& OutColor) const
{
	OutColor = FLinearColor::Red;
	return FSlateIcon(FAppStyle::GetAppStyleSetName(), "ClassIcon.BlendSpace");
}
>>>>>>> 595b50cfd57cee54cfddcf2bb92eddc25d608d11
