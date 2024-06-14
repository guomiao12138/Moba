// Copyright Epic Games, Inc. All Rights Reserved.

#include "AbilityEditorModule.h"
#include "AssetToolsModule.h"
#include "Editor/MobaAbilityEditorToolKit.h"

using namespace EAssetTypeCategories;
#define LOCTEXT_NAMESPACE "AbilityModule"

void FAbilityEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module



	RegisterAssetsAction();
}

void FAbilityEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FAbilityEditorModule::RegisterAssetsAction()
{
}

TSharedRef<FMobaAbilityEditorToolKit> FAbilityEditorModule::CreateAbilityEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UMobaAbility* InAbility)
{
	TSharedRef< FMobaAbilityEditorToolKit > AbilityEditorToolKit(new FMobaAbilityEditorToolKit());
	AbilityEditorToolKit->InitializeAssetEditor(Mode, InitToolkitHost, InAbility);
	return AbilityEditorToolKit;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAbilityEditorModule, AbilityEditorMode)