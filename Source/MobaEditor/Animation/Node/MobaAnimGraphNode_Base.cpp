// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAnimGraphNode_Base.h"

FText UMobaAnimGraphNode_Base::GetMenuCategory() const
{
	return FText::FromString("MobaAnimGraphNode");
}

FText UMobaAnimGraphNode_Base::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(FString::Printf(TEXT("State Slot : %s"), *SlotName.ToString()));
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
		Node.SlotName = PropertyName;
	}	
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(FAnimationGroupReference, Method))
	{
		Node.SetGroupMethod(AnimationGroupReference.Method);
	}
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(FAnimationGroupReference, GroupRole))
	{
		Node.SetGroupRole(AnimationGroupReference.GroupRole);
	}
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(FAnimationGroupReference, GroupName))
	{
		Node.SetGroupName(AnimationGroupReference.GroupName);
	}
	
	PropertyChangeEvent.Broadcast(PropertyChangedEvent);
}

void UMobaAnimGraphNode_Base::GetBoundFunctionsInfo(TArray<TPair<FName, FName>>& InOutBindingsInfo)
{
}
