// Fill out your copyright notice in the Description page of Project Settings.


#include "InputActionAsset.h"
#include "UObject/ObjectSaveContext.h"
#include "GameFramework/PlayerInput.h"

#include "Misc/DefaultValueHelper.h"

void UInputActionAsset::PostLoad()
{
	Super::PostLoad();
}

void UInputActionAsset::PostInitProperties()
{
	Super::PostInitProperties();

	if (CanLoadDefault)
	{
		FString configPath = FConfigCacheIni::NormalizeConfigIniPath(FString::Printf(TEXT("%s%s.ini"), *FPaths::SourceConfigDir(), *GetClass()->ClassConfigName.ToString()));;
		LoadConfig(UInputActionAsset::StaticClass(), *configPath);
		CanLoadDefault = false;
		SaveConfig();
	}
}

#if WITH_EDITOR
void UInputActionAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (!PropertyChangedEvent.Property->HasAnyPropertyFlags(EPropertyFlags::CPF_Config))
	{
		return;
	}
	FString configPath = FConfigCacheIni::NormalizeConfigIniPath(FString::Printf(TEXT("%s%s.ini"), *FPaths::SourceConfigDir(), *GetClass()->ClassConfigName.ToString()));;
	SaveConfig(CPF_Config, *configPath);
}

void UInputActionAsset::PreSaveRoot(FObjectPreSaveRootContext ObjectSaveContext)
{
	Super::PreSaveRoot(ObjectSaveContext);

	SaveConfig();
}

#endif