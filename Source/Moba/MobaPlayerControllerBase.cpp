// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaPlayerControllerBase.h"

AMobaPlayerControllerBase::AMobaPlayerControllerBase()
{
	SetShowMouseCursor(true);
	bEnableClickEvents = true;
}

void AMobaPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
}
