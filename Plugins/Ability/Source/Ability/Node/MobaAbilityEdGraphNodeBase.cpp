// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityEdGraphNodeBase.h"

FText UMobaAbilityEdGraphNodeBase::GetFunctionContextString() const
{
	return FText();
}

void UMobaAbilityEdGraphNodeBase::SetFromFunction(const UFunction* Function)
{
	if (Function != NULL)
	{
		//bIsPureFunc = Function->HasAnyFunctionFlags(FUNC_BlueprintPure);
		//bIsConstFunc = Function->HasAnyFunctionFlags(FUNC_Const);
		//DetermineWantsEnumToExecExpansion(Function);

		FunctionReference.SetFromField<UFunction>(Function, false);
	}
}


void UMobaAbilityEdGraphNodeBase::Init(FName fucnname, FName tooltip)
{
	FuncName = fucnname;
	Tooltip = tooltip;
}

void UMobaAbilityEdGraphNodeBase::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);

	CreatePin(EGPD_Input, TEXT("GraphNodePinCategory"), TEXT("GraphNodePinSubCategory"), nullptr, TEXT("AAAA"));
	CreatePin(EGPD_Output, TEXT("GraphNodePinCategory"), TEXT("GraphNodePinSubCategory"), nullptr, TEXT("BBBB"));
	//CreatePin(EGPD_Output, TEXT("GraphNodePinCategory"), TEXT("GraphNodePinSubCategory"), nullptr, TEXT(""));
}

FText UMobaAbilityEdGraphNodeBase::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromName(FuncName); /*NSLOCTEXT("Editor", "MobaAbility", "Begin");*/
}

FLinearColor UMobaAbilityEdGraphNodeBase::GetNodeTitleColor() const
{
	return FLinearColor::White;
}

FText UMobaAbilityEdGraphNodeBase::GetTooltipText() const
{
	return FText::FromName(Tooltip);
	/*return NSLOCTEXT("EditorExtenstion", "MobaAbility Graph Node Tooltip", "Tooltip");*/
}

//FSlateIcon UMobaAbilityEdGraphNodeBase::GetIconAndTint(FLinearColor& OutColor) const
//{
//	OutColor = GetNodeTitleColor();
//	static FSlateIcon Icon(FAppStyle::GetAppStyleSetName(), "Kismet.AllClasses.FunctionIcon");
//	return Icon;
//}
