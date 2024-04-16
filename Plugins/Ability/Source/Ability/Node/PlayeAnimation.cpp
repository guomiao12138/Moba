// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayeAnimation.h"

#if WITH_EDITOR
FText UPlayeAnimation::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString("PlayeAnimation");
}
#endif

void UPlayeAnimation::OnActiveNode()
{
}

bool UPlayeAnimation::OnDeActiveNode()
{
	return false;
}
