// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAnimGraphNode_Base.h"
#include "Moba/Animation/MobaAnimInstance.h"


FText UMobaAnimGraphNode_Base::GetMenuCategory() const
{
	return FText::FromString("MobaAnimGraphNode");
}

//FText UMobaAnimGraphNode_Base::GetNodeTitle(ENodeTitleType::Type TitleType) const
//{
//	return FText::FromString(FString::Printf(TEXT("State Slot : %s"), *ECharacterType::GetName(SlotName).ToString()));
//}

FLinearColor UMobaAnimGraphNode_Base::GetNodeTitleColor() const
{
	return FLinearColor::Green;
}

void UMobaAnimGraphNode_Base::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UMobaAnimGraphNode_Base, UseCustom))
	{
		if (UseCustom && GetSchema())
		{
			InitialUpdateFunction.SetExternalMember(TEXT("OnSlotInitialUpdate"), UMobaAnimInstance::StaticClass());
			FPropertyChangedEvent OnSlotInitialUpdate(FindFProperty<FProperty>(GetClass()->GetOwnerStruct(), TEXT("InitialUpdateFunction")));
			Super::PostEditChangeProperty(OnSlotInitialUpdate);

			BecomeRelevantFunction.SetExternalMember(TEXT("OnSlotBecomeRelevant"), UMobaAnimInstance::StaticClass());
			FPropertyChangedEvent OnSlotBecomeRelevant(FindFProperty<FProperty>(GetClass()->GetOwnerStruct(), TEXT("OnSlotBecomeRelevant")));
			Super::PostEditChangeProperty(OnSlotBecomeRelevant);

			UpdateFunction.SetExternalMember(TEXT("OnSlotUpdate"), UMobaAnimInstance::StaticClass());
			FPropertyChangedEvent OnSlotUpdate(FindFProperty<FProperty>(GetClass()->GetOwnerStruct(), TEXT("OnSlotUpdate")));
			Super::PostEditChangeProperty(OnSlotUpdate);
		}
	}	
	else
	{
		Super::PostEditChangeProperty(PropertyChangedEvent);
	}
}

void UMobaAnimGraphNode_Base::PostPasteNode()
{
	Super::PostPasteNode();
	if (UseCustom)
	{
		FPropertyChangedEvent EmptyPropertyUpdateStruct(NULL);
		PostEditChangeProperty(EmptyPropertyUpdateStruct);
	}

	//for (TFieldIterator<FProperty> PropertyIt(StructProperty->Struct); PropertyIt; ++PropertyIt)
	//{
	//	if (PropertyIt->GetName() == TEXT("SlotName"))
	//	{
	//		PropertyIt->SetValue_InContainer(StructProperty, &SlotName);
	//	}
	//}
}

void UMobaAnimSequenceNode_Base::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UMobaAnimGraphNode_Base, SlotName))
	{
		static_cast<FMobaAnimNode_Sequence*>(GetFNode())->SlotName = SlotName;
	}
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(FAnimationGroupReference, Method))
	{
		static_cast<FMobaAnimNode_Sequence*>(GetFNode())->SetGroupMethod(AnimationGroupReference.Method);
	}
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(FAnimationGroupReference, GroupRole))
	{
		static_cast<FMobaAnimNode_Sequence*>(GetFNode())->SetGroupRole(AnimationGroupReference.GroupRole);
	}
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(FAnimationGroupReference, GroupName))
	{
		static_cast<FMobaAnimNode_Sequence*>(GetFNode())->SetGroupName(AnimationGroupReference.GroupName);
	}
	else
	{
		Super::PostEditChangeProperty(PropertyChangedEvent);
	}

}

FText UMobaAnimSequenceNode_Base::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(FString::Printf(TEXT("MobaAnimSequence State Slot : %s"), *ECharacterType::GetName(SlotName).ToString()));
}

UMobaAnimBlendSpaceNode_Base::UMobaAnimBlendSpaceNode_Base()
{
	FStructProperty* StructProperty = GetFNodeProperty();

}

FText UMobaAnimBlendSpaceNode_Base::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(FString::Printf(TEXT("MobaAnimBlendSpace State Slot : %s"), *ECharacterType::GetName(SlotName).ToString()));
}

void UMobaAnimBlendSpaceNode_Base::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UMobaAnimGraphNode_Base, SlotName))
	{
		static_cast<FMobaAnimNode_BlendSpace*>(GetFNode())->SlotName = SlotName;
	}
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(FAnimationGroupReference, Method))
	{
		static_cast<FMobaAnimNode_BlendSpace*>(GetFNode())->SetGroupMethod(AnimationGroupReference.Method);
	}
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(FAnimationGroupReference, GroupRole))
	{
		static_cast<FMobaAnimNode_BlendSpace*>(GetFNode())->SetGroupRole(AnimationGroupReference.GroupRole);
	}
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(FAnimationGroupReference, GroupName))
	{
		static_cast<FMobaAnimNode_BlendSpace*>(GetFNode())->SetGroupName(AnimationGroupReference.GroupName);
	}
	else
	{
		Super::PostEditChangeProperty(PropertyChangedEvent);
	}

}

