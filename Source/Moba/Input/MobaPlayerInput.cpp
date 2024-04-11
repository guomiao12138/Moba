// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaPlayerInput.h"
#include "Moba/DataAsset/InputActionAsset.h"

UMobaPlayerInput::UMobaPlayerInput()
{

}

void UMobaPlayerInput::InitInputSetting()
{
	FString configPath = FPaths::ProjectConfigDir() + TEXT("DefaultMoba.ini");
	//GConfig->LoadFile
	//asset->PostLoad();

	UInputActionAsset* asset = FindObject<UInputActionAsset>(nullptr, TEXT("/Game/InputSetting.InputSetting"));
	if(!asset)
	{
		asset = LoadObject<UInputActionAsset>(nullptr, TEXT("/Game/InputSetting.InputSetting"));
	}
	if (!asset)
	{
		return;
	}
	asset->ReloadConfig();

	for (auto ac : asset->ActionMappings)
	{
		FInputActionKeyMapping action;
		action.ActionName = EInputAction::GetName(ac.ActionName);
		action.Key = ac.BaseKey;
		AddActionMapping(action);
	}

	for (auto ax : asset->AxisMappings)
	{
		FInputAxisKeyMapping axis;
		axis.AxisName = EInputAction::GetName(ax.ActionName);
		axis.Key = ax.Key;
		axis.Scale = ax.Scale;
		AddAxisMapping(axis);
	}
}
