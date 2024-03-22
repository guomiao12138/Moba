// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityNode.h"
#include "Ability/Runtime/MobaAbility.h"
#include "Ability/Editor/MobaAbilityEdGraph.h"
#include "Ability/Editor/MobaAbilityEditorToolKit.h"

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


FText UAbilityNode::GetFunctionContextString() const
{
	return FText();
}


void UAbilityNode::CreateParamsPins()
{

	//for (TFieldIterator<FProperty> PropIt(Function); PropIt && (PropIt->PropertyFlags & CPF_Parm); ++PropIt)
	for (FProperty* Property = GetClass()->PropertyLink; Property != nullptr; Property = Property->PropertyLinkNext)
	{
		if (Property->Owner != GetClass())
		{
			continue;
		}
		//FProperty* Param = Property;

		//const bool bIsFunctionInput = !Property->HasAnyPropertyFlags(CPF_ReturnParm) && (!Property->HasAnyPropertyFlags(CPF_OutParm) || Property->HasAnyPropertyFlags(CPF_ReferenceParm));
		//const bool bIsRefParam = Property->HasAnyPropertyFlags(CPF_ReferenceParm) && bIsFunctionInput;

		const EEdGraphPinDirection Direction = EGPD_Input;

		UEdGraphNode::FCreatePinParams PinParams;
		//PinParams.bIsReference = bIsRefParam;

		UEdGraphPin* OwnerPin = nullptr;
		uint64 CastFlags = Property->GetCastFlags();
		if ((CastFlags & CASTCLASS_FBoolProperty) != 0)
		{
			OwnerPin = CreatePin(Direction, UEdGraphSchema_K2::PC_Boolean, Property->GetFName(), PinParams);
		}
		else if ((CastFlags & CASTCLASS_FNameProperty) != 0)
		{
			OwnerPin = CreatePin(Direction, UEdGraphSchema_K2::PC_Name, Property->GetFName(), PinParams);
		}
		else if ((CastFlags & CASTCLASS_FObjectPropertyBase) != 0)
		{
			FObjectProperty* temp = CastField<FObjectProperty>(Property);
			OwnerPin = CreatePin(Direction, UEdGraphSchema_K2::PC_SoftObject, temp->PropertyClass, Property->GetFName());
		}
		//UEdGraphPin* OwnerPin = CreatePin(Direction, UEdGraphSchema_K2::PC_Class, AActor::StaticClass(), Param->GetFName());
		//FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString::Printf(TEXT("Editor Print Action With Pin Hello World with point %s"), *Param->GetName())));

		//OwnerPin->bAdvancedView = true;
	}

}

UEdGraphPin* UAbilityNode::GetExecutePin()
{
	return FindPin(UEdGraphSchema_K2::PN_Execute);
}

UEdGraphPin* UAbilityNode::GetThenPin()
{
	if (Succeed)
	{
		return FindPin(TEXT("Succeed"));
	}
	else
	{
		return FindPin(TEXT("Faild"));
	}
}

void UAbilityNode::Tick(float DeltaTime)
{

	if (CanTick && Succeed)
	{


	}

	Cast<UAbilityNode>(GetThenPin()->GetOwningNode())->Tick(DeltaTime);
}

void UAbilityNode::OnActiveNode()
{
	Succeed = true;
}

APawn* UAbilityNode::GetCauser()
{
	if (auto graph = GetOuter())
	{
		if (auto ability = Cast<UMobaAbility>(graph->GetOuter()))
		{
			return ability->Owner;
		}
	}

	return nullptr;
}

UAbilityNode::UAbilityNode()
{

}

void UAbilityNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, TEXT("Succeed"));
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, TEXT("Faild"));

	CreateParamsPins();
}

FText UAbilityNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(GetClass()->GetName()); 
}

FLinearColor UAbilityNode::GetNodeTitleColor() const
{
	return FLinearColor::White;
}

FText UAbilityNode::GetTooltipText() const
{
	return  FText();
	/*return NSLOCTEXT("EditorExtenstion", "MobaAbility Graph Node Tooltip", "Tooltip");*/
}

UObject* UAbilityNode::GetJumpTargetForDoubleClick() const
{
	return nullptr;
}

bool UAbilityNode::CanJumpToDefinition() const
{
	return true;
}

void UAbilityNode::JumpToDefinition() const
{
	//if (ensure(GUnrealEd) && GUnrealEd->GetUnrealEdOptions()->IsCPPAllowed())
	//{
	//	// For native functions, try going to the function definition in C++ if available
	//	if (UFunction* TargetFunction = UMobaAbility::StaticClass()->FindFunctionByName(FunctionReference.GetMemberName()))
	//	{
	//		if (TargetFunction->IsNative())
	//		{
	//			// First try the nice way that will get to the right line number
	//			bool bSucceeded = false;
	//			const bool bNavigateToNativeFunctions = GetDefault<UBlueprintEditorSettings>()->bNavigateToNativeFunctionsFromCallNodes;

	//			if (bNavigateToNativeFunctions)
	//			{
	//				if (FSourceCodeNavigation::CanNavigateToFunction(TargetFunction))
	//				{
	//					bSucceeded = FSourceCodeNavigation::NavigateToFunction(TargetFunction);
	//				}

	//				// Failing that, fall back to the older method which will still get the file open assuming it exists
	//				if (!bSucceeded)
	//				{
	//					FString NativeParentClassHeaderPath;
	//					const bool bFileFound = FSourceCodeNavigation::FindClassHeaderPath(TargetFunction, NativeParentClassHeaderPath) && (IFileManager::Get().FileSize(*NativeParentClassHeaderPath) != INDEX_NONE);
	//					if (bFileFound)
	//					{
	//						const FString AbsNativeParentClassHeaderPath = FPaths::ConvertRelativePathToFull(NativeParentClassHeaderPath);
	//						bSucceeded = FSourceCodeNavigation::OpenSourceFile(AbsNativeParentClassHeaderPath);
	//					}
	//				}
	//			}
	//			else
	//			{
	//				// Inform user that the function is native, give them opportunity to enable navigation to native
	//				// functions:
	//				FNotificationInfo Info(FText::FromString("Navigation to Native (c++) Functions Disabled"));
	//				Info.ExpireDuration = 10.0f;
	//				Info.CheckBoxState = bNavigateToNativeFunctions ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;

	//				Info.CheckBoxStateChanged = FOnCheckStateChanged::CreateStatic(
	//					[](ECheckBoxState NewState)
	//					{
	//						const FScopedTransaction Transaction(FText::FromString("ChangeNavigateToNative FunctionsFromCallNodes Change Navigate to Native Functions from Call Nodes Setting"));

	//						UBlueprintEditorSettings* MutableEditorSetings = GetMutableDefault<UBlueprintEditorSettings>();
	//						MutableEditorSetings->Modify();
	//						MutableEditorSetings->bNavigateToNativeFunctionsFromCallNodes = (NewState == ECheckBoxState::Checked) ? true : false;
	//						MutableEditorSetings->SaveConfig();
	//					}
	//				);
	//				Info.CheckBoxText = FText::FromString("EnableNavigationToNative Navigate to Native Functions from Blueprint Call Nodes?");

	//				FSlateNotificationManager::Get().AddNotification(Info);
	//			}

	//			return;
	//		}
	//	}
	//}

	// Otherwise, fall back to the inherited behavior which should go to the function entry node
	Super::JumpToDefinition();
}

void UAbilityNode::PinConnectionListChanged(UEdGraphPin* Pin)
{
}
