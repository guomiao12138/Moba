// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaPlayerInput.h"
#include "UObject/ConstructorHelpers.h"
#include "Moba/DataAsset/InputActionAsset.h"

UMobaPlayerInput::UMobaPlayerInput()
{
	ConstructorHelpers::FObjectFinder<UInputActionAsset> Setting(TEXT("/Game/NewDataAsset.NewDataAsset"));
	Setting.Object->ActionMappings;



}

void UMobaPlayerInput::InitInputSetting()
{
	UInputActionAsset* asset = FindObject<UInputActionAsset>(nullptr, TEXT("/Game/NewDataAsset.NewDataAsset"));
	if(!asset)
	{
		asset = LoadObject<UInputActionAsset>(nullptr, TEXT("/Game/NewDataAsset.NewDataAsset"));
	}


	for (auto ac : asset->ActionMappings)
	{
		FInputActionKeyMapping action;
		action.ActionName = EInputAction::GetName(ac.ActionName);
		action.Key = ac.BaseKey;
		AddActionMapping(action);
	}
}
