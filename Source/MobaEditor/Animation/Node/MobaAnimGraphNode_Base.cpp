// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAnimGraphNode_Base.h"
#include "Moba/Animation/MobaAnimInstance.h"

FText UMobaAnimGraphNode_Base::GetMenuCategory() const
{
	return FText::FromString("MobaAnimGraphNode");
}

FText UMobaAnimGraphNode_Base::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(FString::Printf(TEXT("State Slot : %s"), *ECharacterType::GetName(SlotName).ToString()));
}

FLinearColor UMobaAnimGraphNode_Base::GetNodeTitleColor() const
{
	return FLinearColor::Green;
}

void UMobaAnimGraphNode_Base::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UMobaAnimGraphNode_Base, SlotName))
	{
		static_cast<FMobaAnimNode_base*>(GetFNode())->SlotName = SlotName;
	}	
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(FAnimationGroupReference, Method))
	{
		static_cast<FMobaAnimNode_base*>(GetFNode())->SetGroupMethod(AnimationGroupReference.Method);
	}
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(FAnimationGroupReference, GroupRole))
	{
		static_cast<FMobaAnimNode_base*>(GetFNode())->SetGroupRole(AnimationGroupReference.GroupRole);
	}
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(FAnimationGroupReference, GroupName))
	{
		static_cast<FMobaAnimNode_base*>(GetFNode())->SetGroupName(AnimationGroupReference.GroupName);
	}

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
	else
	{
		PropertyChangeEvent.Broadcast(PropertyChangedEvent);
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
	if (SlotName != ECharacterType::None)
	{
		Node.SlotName = SlotName;
	}

}
