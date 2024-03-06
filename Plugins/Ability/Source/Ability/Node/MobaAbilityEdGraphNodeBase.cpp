// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityEdGraphNodeBase.h"
#include "Ability/MobaAbility.h"
#include "Ability/MobaAbilityEdGraph.h"
#include "Ability/MobaAbilityEditorToolKit.h"

#include "Kismet/KismetSystemLibrary.h"
#include "SGraphNode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"
#include "WorkflowOrientedApp/WorkflowUObjectDocuments.h"
#include "Editor/BlueprintGraph/Public/BlueprintEditorSettings.h"
#include "Editor/UnrealEd/Public/SourceCodeNavigation.h"
#include "Editor/UnrealEd/Public/UnrealEdGlobals.h"
#include "Editor/UnrealEd/Classes/Editor/UnrealEdEngine.h"
#include "Preferences/UnrealEdOptions.h"

#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"


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

UEdGraphPin* UMobaAbilityEdGraphNodeBase::GetExecutePin()
{
	return FindPin(UEdGraphSchema_K2::PN_Execute);
}

UEdGraphPin* UMobaAbilityEdGraphNodeBase::GetThenPin()
{
	return FindPin(UEdGraphSchema_K2::PN_Then);
}

void UMobaAbilityEdGraphNodeBase::SetNodeTitle(FName name)
{
	FunctionReference.SetMemberName(name);
}

void UMobaAbilityEdGraphNodeBase::CallFunction()
{
	GetOuter()->GetOuter()->ProcessEvent(FunctionReference.GetMemberParentClass()->FindFunctionByName(FunctionReference.GetMemberName()), NULL);
}


//void UMobaAbilityEdGraphNodeBase::Init(FName fucnname, FName tooltip)
//{
//	FuncName = fucnname;
//	Tooltip = tooltip;
//}

UMobaAbilityEdGraphNodeBase::UMobaAbilityEdGraphNodeBase()
{

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
	return  FText::FromName(FunctionReference.GetMemberName());
	/*return NSLOCTEXT("EditorExtenstion", "MobaAbility Graph Node Tooltip", "Tooltip");*/
}

UObject* UMobaAbilityEdGraphNodeBase::GetJumpTargetForDoubleClick() const
{
	return nullptr;
}

bool UMobaAbilityEdGraphNodeBase::CanJumpToDefinition() const
{
	if (FunctionReference.GetMemberName().IsNone())
	{
		return false;
	}
	return true;
}

void UMobaAbilityEdGraphNodeBase::JumpToDefinition() const
{
	if (ensure(GUnrealEd) && GUnrealEd->GetUnrealEdOptions()->IsCPPAllowed())
	{
		// For native functions, try going to the function definition in C++ if available
		if (UFunction* TargetFunction = UMobaAbility::StaticClass()->FindFunctionByName(FunctionReference.GetMemberName()))
		{
			if (TargetFunction->IsNative())
			{
				// First try the nice way that will get to the right line number
				bool bSucceeded = false;
				const bool bNavigateToNativeFunctions = GetDefault<UBlueprintEditorSettings>()->bNavigateToNativeFunctionsFromCallNodes;

				if (bNavigateToNativeFunctions)
				{
					if (FSourceCodeNavigation::CanNavigateToFunction(TargetFunction))
					{
						bSucceeded = FSourceCodeNavigation::NavigateToFunction(TargetFunction);
					}

					// Failing that, fall back to the older method which will still get the file open assuming it exists
					if (!bSucceeded)
					{
						FString NativeParentClassHeaderPath;
						const bool bFileFound = FSourceCodeNavigation::FindClassHeaderPath(TargetFunction, NativeParentClassHeaderPath) && (IFileManager::Get().FileSize(*NativeParentClassHeaderPath) != INDEX_NONE);
						if (bFileFound)
						{
							const FString AbsNativeParentClassHeaderPath = FPaths::ConvertRelativePathToFull(NativeParentClassHeaderPath);
							bSucceeded = FSourceCodeNavigation::OpenSourceFile(AbsNativeParentClassHeaderPath);
						}
					}
				}
				else
				{
					// Inform user that the function is native, give them opportunity to enable navigation to native
					// functions:
					FNotificationInfo Info(FText::FromString("Navigation to Native (c++) Functions Disabled"));
					Info.ExpireDuration = 10.0f;
					Info.CheckBoxState = bNavigateToNativeFunctions ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;

					Info.CheckBoxStateChanged = FOnCheckStateChanged::CreateStatic(
						[](ECheckBoxState NewState)
						{
							const FScopedTransaction Transaction(FText::FromString("ChangeNavigateToNative FunctionsFromCallNodes Change Navigate to Native Functions from Call Nodes Setting"));

							UBlueprintEditorSettings* MutableEditorSetings = GetMutableDefault<UBlueprintEditorSettings>();
							MutableEditorSetings->Modify();
							MutableEditorSetings->bNavigateToNativeFunctionsFromCallNodes = (NewState == ECheckBoxState::Checked) ? true : false;
							MutableEditorSetings->SaveConfig();
						}
					);
					Info.CheckBoxText = FText::FromString("EnableNavigationToNative Navigate to Native Functions from Blueprint Call Nodes?");

					FSlateNotificationManager::Get().AddNotification(Info);
				}

				return;
			}
		}
	}

	// Otherwise, fall back to the inherited behavior which should go to the function entry node
	Super::JumpToDefinition();
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
