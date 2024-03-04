// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityEdGraphNodeBase.h"
#include "K2Node_CallFunction.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Editor/KismetCompiler/Public/KismetCompiler.h"
#include "Ability/MobaAbility.h"

#include "SGraphNode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"
#include "WorkflowOrientedApp/WorkflowUObjectDocuments.h"

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

void UMobaAbilityEdGraphNodeBase::SetDoubleClickEvent(FSingleNodeEvent InSingleNodeEvent)
{
	//FSingleNodeEvent SingleNodeEvent;
	//SingleNodeEvent.BindUFunction(this, FName("JumpToDefinition"));
	//CreateVisualWidget().Get()->SetDoubleClickEvent(SingleNodeEvent);
}


//void UMobaAbilityEdGraphNodeBase::Init(FName fucnname, FName tooltip)
//{
//	FuncName = fucnname;
//	Tooltip = tooltip;
//}

UMobaAbilityEdGraphNodeBase::UMobaAbilityEdGraphNodeBase()
{
	DocumentManager = MakeShareable(new FDocumentTracker);
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
	return FText::FromName(FunctionReference.GetMemberName()); /*NSLOCTEXT("Editor", "MobaAbility", "Begin");*/
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

UObject* UMobaAbilityEdGraphNodeBase::GetJumpTargetForDoubleClick() const
{
	return nullptr;
}

bool UMobaAbilityEdGraphNodeBase::CanJumpToDefinition() const
{
	if (FuncName.IsNone())
	{
		return false;
	}
	return true;
}

void UMobaAbilityEdGraphNodeBase::JumpToDefinition() const
{
	TSharedPtr<SGraphEditor> GraphEditor;
	//if (bRequestRename)
	//{
	//	// If we are renaming, the graph will be open already, just grab the tab and it's content and jump to the node.
	//	TSharedPtr<SDockTab> ActiveTab = DocumentManager->GetActiveTab();
	//	check(ActiveTab.IsValid());
	//	GraphEditor = StaticCastSharedRef<SGraphEditor>(ActiveTab->GetContent());
	//}
	//else
	//{
	//	// Open a graph editor and jump to the node

		TSharedRef<FTabPayload_UObject> Payload = FTabPayload_UObject::Make(Cast<UEdGraph>(GetOuter()));

		TSharedPtr<SDockTab> TabWithGraph = DocumentManager->OpenDocument(Payload, FDocumentTracker::OpenNewDocument);
		//if (TabWithGraph.IsValid())
		//{

			// We know that the contents of the opened tabs will be a graph editor.
		GraphEditor = StaticCastSharedRef<SGraphEditor>(TabWithGraph->GetContent());
		GraphEditor->CaptureKeyboard();

	//}

	if (GraphEditor.IsValid())
	{
		GraphEditor->JumpToNode(this, false);
	}
}

//TSharedPtr<SGraphEditor> UMobaAbilityEdGraphNodeBase::OpenGraphAndBringToFront(UEdGraph* Graph, bool bSetFocus)
//{
//	if (!IsValid(Graph))
//	{
//		return TSharedPtr<SGraphEditor>();
//	}
//
//	// First, switch back to standard mode
//	//SetCurrentMode(FBlueprintEditorApplicationModes::StandardBlueprintEditorMode);
//
//	// This will either reuse an existing tab or spawn a new one
//	TSharedRef<FTabPayload_UObject> Payload = FTabPayload_UObject::Make(Graph);
//
//	TSharedPtr<SDockTab> TabWithGraph = DocumentManager->OpenDocument(Payload, FDocumentTracker::OpenNewDocument);
//	if (TabWithGraph.IsValid())
//	{
//
//		// We know that the contents of the opened tabs will be a graph editor.
//		TSharedRef<SGraphEditor> NewGraphEditor = StaticCastSharedRef<SGraphEditor>(TabWithGraph->GetContent());
//		NewGraphEditor->CaptureKeyboard();
//
//		// Handover the keyboard focus to the new graph editor widget.
//		if (bSetFocus)
//		{
//		}
//
//		return NewGraphEditor;
//	}
//	else
//	{
//		return TSharedPtr<SGraphEditor>();
//	}
//}

//void UMobaAbilityEdGraphNodeBase::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
//{
//	Super::ExpandNode(CompilerContext, SourceGraph);
//
//	UEdGraphPin* ExecPin = GetExecPin();
//	UEdGraphPin* ThenPin = GetThenPin();
//	if (ExecPin && ThenPin) {
//
//		// create a CallFunction node
//		//FName MyFunctionName = GET_FUNCTION_NAME_CHECKED(UMobaAbility, FuncName);
//
//		UK2Node_CallFunction* CallFuncNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
//		CallFuncNode->FunctionReference.SetExternalMember(FuncName, UMobaAbility::StaticClass());
//		CallFuncNode->AllocateDefaultPins();
//
//		// move pins
//		CompilerContext.MovePinLinksToIntermediate(*ExecPin, *(CallFuncNode->GetExecPin()));
//		CompilerContext.MovePinLinksToIntermediate(*ThenPin, *(CallFuncNode->GetThenPin()));
//	}
//
//	BreakAllNodeLinks();
//}

//FSlateIcon UMobaAbilityEdGraphNodeBase::GetIconAndTint(FLinearColor& OutColor) const
//{
//	OutColor = GetNodeTitleColor();
//	static FSlateIcon Icon(FAppStyle::GetAppStyleSetName(), "Kismet.AllClasses.FunctionIcon");
//	return Icon;
//}
