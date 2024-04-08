// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack.h"

FText UAttack::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString("Attack");
}

void UAttack::OnActiveNode()
{
}

bool UAttack::OnDeActiveNode()
{
	return false;
}
