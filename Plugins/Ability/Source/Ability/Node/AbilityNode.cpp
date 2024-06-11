// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityNode.h"
#include "Ability/MobaAbility.h"
#include "Misc/Variant.h"
#include "Kismet/KismetSystemLibrary.h"
//#include "Editor/BlueprintGraph/Public/BlueprintEditorSettings.h"
//#include "Editor/UnrealEd/Public/SourceCodeNavigation.h"
//#include "Editor/UnrealEd/Public/UnrealEdGlobals.h"
//#include "Editor/UnrealEd/Classes/Editor/UnrealEdEngine.h"
//#include "Preferences/UnrealEdOptions.h"
#include "Misc/DefaultValueHelper.h"
#include "UObject/ConstructorHelpers.h"
//#include "Framework/Notifications/NotificationManager.h"
//#include "Widgets/Notifications/SNotificationList.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraph.h"

void UAbilityNode::Tick(float DeltaTime)
{

	if (CanTick && Succeed)
	{


	}

	for (auto sub : SubNodes)
	{
		sub->Tick(DeltaTime);
	}
	//Cast<UAbilityNode>(GetThenPin()->GetOwningNode())->Tick(DeltaTime);
}

void UAbilityNode::OnActiveNode()
{
	Succeed = true;
	TArray<UAbilityNode*> Nodes;

	for (UEdGraphPin* Pin : Pins)
	{
		if (Pin->LinkedTo.Num() > 0 && Pin->Direction == EGPD_Output)
		{
			for (UEdGraphPin* Connection : Pin->LinkedTo)
			{
				// avoid including the current node in the case of a self connection:
				if (Connection->GetOwningNode() != this)
				{
					//PinDefaultValueChanged(Connection);
					//NeighborsAcceptedForConsideration.Add(Connection->GetOwningNode());
					Cast<UAbilityNode>(Connection->GetOwningNode())->OnActiveNode();
				}
			}
		}
	}
}

ACharacter* UAbilityNode::GetOwnerPawn()
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

#if WITH_EDITOR

UEdGraphPin* UAbilityNode::GetExecutePin()
{
	return FindPinChecked(TEXT("Execute"));
}

UEdGraphPin* UAbilityNode::GetThenPin()
{
	if (Succeed)
	{
		return FindPinChecked(TEXT("Succeed"));
	}
	else
	{
		return FindPinChecked(TEXT("Faild"));
	}
}

void UAbilityNode::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (auto pin = FindPin(PropertyChangedEvent.GetPropertyName()))
	{
		for (FProperty* Property = GetClass()->PropertyLink; Property != nullptr; Property = Property->PropertyLinkNext)
		{
			if (Property->Owner != GetClass() || Property->HasAnyPropertyFlags(EPropertyFlags::CPF_SimpleDisplay))
			{
				continue;
			}
			if (PropertyChangedEvent.GetPropertyName() == Property->GetName())
			{
				Property = PropertyChangedEvent.Property;
			}

			uint64 CastFlags = PropertyChangedEvent.Property->GetCastFlags();
			if ((CastFlags & CASTCLASS_FObjectPropertyBase) != 0)
			{
				if (FObjectPtrProperty* ObjectProperty = CastField<FObjectPtrProperty>(Property))
				{
					void* ObjectContainer = ObjectProperty->ContainerPtrToValuePtr<void>(this);
					UObject* TargetObject = ObjectProperty->GetObjectPropertyValue(ObjectContainer);

					pin->DefaultObject = TargetObject;
					if (pin->DefaultObject)
					{
						pin->DefaultValue = pin->DefaultObject->GetPathName();
					}
					else
					{
						pin->ResetDefaultValue();
					}
				}



			}
		}


	}
}

void UAbilityNode::ReconstructNode()
{
	for (auto pin : Pins)
	{
		pin->BreakAllPinLinks(true);
	}
	Pins.Empty();
	Modify();
	AllocateDefaultPins();
	CreateParamsPins();

	GetGraph()->NotifyNodeChanged(this);
}

void UAbilityNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, TEXT("exec"), TEXT("Execute"));
	CreatePin(EGPD_Output, TEXT("exec"), TEXT("Succeed"));
	CreatePin(EGPD_Output, TEXT("exec"), TEXT("Faild"));
}

void UAbilityNode::CreateParamsPins()
{
	//for (TFieldIterator<FProperty> PropIt(Function); PropIt && (PropIt->PropertyFlags & CPF_Parm); ++PropIt)
	for (FProperty* Property = GetClass()->PropertyLink; Property != nullptr; Property = Property->PropertyLinkNext)
	{
		if (Property->Owner != GetClass() || Property->HasAnyPropertyFlags(EPropertyFlags::CPF_SimpleDisplay))
		{
			continue;
		}
		//FProperty* Param = Property;

		//const bool bIsFunctionInput = !Property->HasAnyPropertyFlags(CPF_ReturnParm) && (!Property->HasAnyPropertyFlags(CPF_OutParm) || Property->HasAnyPropertyFlags(CPF_ReferenceParm));
		//const bool bIsRefParam = Property->HasAnyPropertyFlags(CPF_ReferenceParm) && bIsFunctionInput;

		const EEdGraphPinDirection Direction = EGPD_Input;
		UEdGraphNode::FCreatePinParams PinParams;
		PinParams.bIsReference = false;

		UEdGraphPin* OwnerPin = nullptr;
		uint64 CastFlags = Property->GetCastFlags();
		if ((CastFlags & CASTCLASS_FBoolProperty) != 0)
		{
			OwnerPin = CreatePin(Direction, TEXT("bool"), Property->GetFName());
		}
		else if ((CastFlags & CASTCLASS_FNameProperty) != 0)
		{
			OwnerPin = CreatePin(Direction, TEXT("name"), Property->GetFName());
		}
		else if ((CastFlags & CASTCLASS_FObjectPropertyBase) != 0)
		{
			FObjectProperty* temp = CastField<FObjectProperty>(Property);
			OwnerPin = CreatePin(Direction, TEXT("softobject"), temp->PropertyClass, Property->GetFName(), PinParams);
		}
		else if ((CastFlags & CASTCLASS_FFloatProperty) != 0)
		{
			OwnerPin = CreatePin(Direction, TEXT("real"), TEXT("float"), Property->GetFName());
		}
		else if ((CastFlags & CASTCLASS_FIntProperty) != 0)
		{
			OwnerPin = CreatePin(Direction, TEXT("real"), TEXT("int"), Property->GetFName());
		}
		//UEdGraphPin* OwnerPin = CreatePin(Direction, UEdGraphSchema_K2::PC_Class, AActor::StaticClass(), Param->GetFName());
		//FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString::Printf(TEXT("Editor Print Action With Pin Hello World with point %s"), *Param->GetName())));

		if (OwnerPin)
		{
			OwnerPin->bAdvancedView = false;
		}
	}

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

void UAbilityNode::PinConnectionListChanged(UEdGraphPin* Pin)
{
	ForEachNodeDirectlyConnectedToOutputs([&](UEdGraphNode* ChildNode)
		{
			SubNodes.Add(Cast<UAbilityNode>(ChildNode));
		}
	);
}

void UAbilityNode::PostPlacedNewNode()
{
	CreateParamsPins();
}

void UAbilityNode::PinDefaultValueChanged(UEdGraphPin* Pin)
{
	for (FProperty* Property = GetClass()->PropertyLink; Property != nullptr; Property = Property->PropertyLinkNext)
	{		
		if (Property->Owner != GetClass() || Property->HasAnyPropertyFlags(EPropertyFlags::CPF_SimpleDisplay))
		{
			continue;
		}

		if (Property->GetName() == Pin->PinName)
		{
			uint64 CastFlags = Property->GetCastFlags();

			if ((CastFlags & CASTCLASS_FBoolProperty) != 0)
			{
			}
			else if ((CastFlags & CASTCLASS_FNameProperty) != 0)
			{
				Property->SetValue_InContainer(this, *Pin->DefaultValue);
			}
			else if ((CastFlags & CASTCLASS_FObjectPropertyBase) != 0)
			{
				FString ObjectPathLocal;
				if (Pin->DefaultObject && Pin->DefaultValue.IsEmpty())
				{
					ObjectPathLocal = Pin->DefaultObject->GetPathName();
				}
				else
				{
					ObjectPathLocal = Pin->DefaultValue;
				}
				
				ConstructorHelpers::StripObjectClass(ObjectPathLocal);

				if (FPackageName::IsValidObjectPath(ObjectPathLocal))
				{
					FSoftObjectPath AssetRef = ObjectPathLocal;
					UObject* Object = AssetRef.TryLoad();
					if (FObjectPtrProperty* ObjectProperty = CastField<FObjectPtrProperty>(Property))
					{
						void* ObjectContainer = ObjectProperty->ContainerPtrToValuePtr<void>(this);
						UObject* TargetObject = ObjectProperty->GetObjectPropertyValue(ObjectContainer);
						if (Object)
						{
							ObjectProperty->SetObjectPropertyValue(ObjectContainer, Object);
						}
						else
						{
							ObjectProperty->ClearValue(ObjectContainer);
						}
						Pin->ResetDefaultValue();
						Pin->DefaultObject = Object;
					}
				}

			}
			else if ((CastFlags & CASTCLASS_FFloatProperty) != 0)
			{
				float value;
				FDefaultValueHelper::ParseFloat(Pin->DefaultValue, value);
				Property->SetValue_InContainer(this, &value);
			}
			else if ((CastFlags & CASTCLASS_FIntProperty) != 0)
			{
				int value;
				FDefaultValueHelper::ParseInt(Pin->DefaultValue, value);
				Property->SetValue_InContainer(this, &value);
			}


		}

	}
}

#endif

