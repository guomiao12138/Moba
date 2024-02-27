// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityEdGraphNodeBase.h"
#include "K2Node_CallFunction.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Editor/KismetCompiler/Public/KismetCompiler.h"
#include "Ability/MobaAbility.h"

FText UMobaAbilityEdGraphNodeBase::GetFunctionContextString() const
{
	return FText();
}

//void UMobaAbilityEdGraphNodeBase::SetFromFunction(const UFunction* Function)
//{
//	if (Function != NULL)
//	{
//		//bIsPureFunc = Function->HasAnyFunctionFlags(FUNC_BlueprintPure);
//		//bIsConstFunc = Function->HasAnyFunctionFlags(FUNC_Const);
//		//DetermineWantsEnumToExecExpansion(Function);
//
//		FunctionReference.SetFromField<UFunction>(Function, false);
//	}
//}


void UMobaAbilityEdGraphNodeBase::Init(FName fucnname, FName tooltip)
{
	FuncName = fucnname;
	Tooltip = tooltip;
}

void UMobaAbilityEdGraphNodeBase::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);

	//CreatePin(EGPD_Input, TEXT("GraphNodePinCategory"), TEXT("GraphNodePinSubCategory"), nullptr, TEXT("AAAA"));
	//CreatePin(EGPD_Output, TEXT("GraphNodePinCategory"), TEXT("GraphNodePinSubCategory"), nullptr, TEXT("BBBB"));
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

void UMobaAbilityEdGraphNodeBase::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	UEdGraphPin* ExecPin = GetExecPin();
	UEdGraphPin* ThenPin = GetThenPin();
	if (ExecPin && ThenPin) {

		// create a CallFunction node
		//FName MyFunctionName = GET_FUNCTION_NAME_CHECKED(UMobaAbility, FuncName);

		UK2Node_CallFunction* CallFuncNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
		CallFuncNode->FunctionReference.SetExternalMember(FuncName, UMobaAbility::StaticClass());
		CallFuncNode->AllocateDefaultPins();

		// move pins
		CompilerContext.MovePinLinksToIntermediate(*ExecPin, *(CallFuncNode->GetExecPin()));
		CompilerContext.MovePinLinksToIntermediate(*ThenPin, *(CallFuncNode->GetThenPin()));
	}

	BreakAllNodeLinks();
}

//FSlateIcon UMobaAbilityEdGraphNodeBase::GetIconAndTint(FLinearColor& OutColor) const
//{
//	OutColor = GetNodeTitleColor();
//	static FSlateIcon Icon(FAppStyle::GetAppStyleSetName(), "Kismet.AllClasses.FunctionIcon");
//	return Icon;
//}
