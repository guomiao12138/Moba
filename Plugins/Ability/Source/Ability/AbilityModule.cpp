// Copyright Epic Games, Inc. All Rights Reserved.

#include "AbilityModule.h"
#include "AbilityEditorModeCommands.h"
#include "AssetToolsModule.h"

#define LOCTEXT_NAMESPACE "AbilityModule"

void FAbilityModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FAbilityEditorModeCommands::Register();


	RegisterAssetsAction();
}

void FAbilityModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	FAbilityEditorModeCommands::Unregister();
	if (!FModuleManager::Get().IsModuleLoaded("AssetTools")) return;

	if (AbilityAssetTypeAction.IsValid())
	{
		FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(AbilityAssetTypeAction.ToSharedRef());
	}
}

void FAbilityModule::RegisterAssetsAction()
{
	IAssetTools& AssetToolModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	EAssetTypeCategories::Type Category = AssetToolModule.RegisterAdvancedAssetCategory(FName(TEXT("MobaAbility")), NSLOCTEXT("Editor", "MobaAbility", "MobaAbilityAsset"));

	AbilityAssetTypeAction = MakeShared<FAbilityAssetTypeAction>(Category);
	if (AbilityAssetTypeAction.IsValid())
	{
		FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(AbilityAssetTypeAction.ToSharedRef());
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAbilityModule, AbilityEditorMode)