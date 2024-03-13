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

void UMobaAbilityEdGraphNodeBase::CreateParamsPins()
{
	FName funcName = FunctionReference.GetMemberName();
	UFunction* Function = FunctionReference.GetMemberParentClass()->FindFunctionByName(funcName);

	for (TFieldIterator<FProperty> PropIt(Function); PropIt && (PropIt->PropertyFlags & CPF_Parm); ++PropIt)
	{
		FProperty* Param = *PropIt;

		const bool bIsFunctionInput = !Param->HasAnyPropertyFlags(CPF_ReturnParm) && (!Param->HasAnyPropertyFlags(CPF_OutParm) || Param->HasAnyPropertyFlags(CPF_ReferenceParm));
		const bool bIsRefParam = Param->HasAnyPropertyFlags(CPF_ReferenceParm) && bIsFunctionInput;

		const EEdGraphPinDirection Direction = bIsFunctionInput ? EGPD_Input : EGPD_Output;

		UEdGraphNode::FCreatePinParams PinParams;
		PinParams.bIsReference = bIsRefParam;

		UEdGraphPin* OwnerPin = nullptr;
		uint64 CastFlags = PropIt.GetStruct()->ChildProperties->GetCastFlags();
		if ((CastFlags & CASTCLASS_FBoolProperty) != 0)
		{
			OwnerPin = CreatePin(Direction, UEdGraphSchema_K2::PC_Boolean, Param->GetFName(), PinParams);
		}
		else if ((CastFlags & CASTCLASS_FNameProperty) != 0)
		{
			OwnerPin = CreatePin(Direction, UEdGraphSchema_K2::PC_Name, Param->GetFName(), PinParams);
		}
		else if ((CastFlags & CASTCLASS_FObjectPropertyBase) != 0)
		{
			FObjectProperty* temp = CastField<FObjectProperty>(Param);
			OwnerPin = CreatePin(Direction, UEdGraphSchema_K2::PC_SoftObject, temp->PropertyClass, Param->GetFName());
		}
		//UEdGraphPin* OwnerPin = CreatePin(Direction, UEdGraphSchema_K2::PC_Class, AActor::StaticClass(), Param->GetFName());
		//FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString::Printf(TEXT("Editor Print Action With Pin Hello World with point %s"), *Param->GetName())));

		//OwnerPin->bAdvancedView = true;
	}

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

APawn* UMobaAbilityEdGraphNodeBase::GetCauser()
{
	if (auto graph = GetOuter())
	{
		if (auto ability = Cast<UMobaAbility>(graph->GetOuter()))
		{
			return ability->GetOwner();
		}
	}

	return nullptr;
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
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, TEXT("Succeed"));
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, TEXT("Faild"));

	CreateParamsPins();
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