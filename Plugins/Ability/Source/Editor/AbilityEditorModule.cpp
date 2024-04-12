// Copyright Epic Games, Inc. All Rights Reserved.

#include "AbilityEditorModule.h"
#include "AssetToolsModule.h"
#include "Editor/MobaAbilityEditorToolKit.h"
#include "Editor/AbilityAssetTypeAction.h"

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

	if (!FModuleManager::Get().IsModuleLoaded("AssetTools")) return;

	if (AbilityAssetTypeAction.IsValid())
	{
		FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(AbilityAssetTypeAction.ToSharedRef());
	}
}

void FAbilityEditorModule::RegisterAssetsAction()
{
	IAssetTools& AssetToolModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	EAssetTypeCategories::Type Category = AssetToolModule.RegisterAdvancedAssetCategory(FName(TEXT("MobaAbility")), NSLOCTEXT("Editor", "MobaAbility", "MobaAbilityAsset"));

	AbilityAssetTypeAction = MakeShareable(new FAbilityAssetTypeAction(Category));
	if (AbilityAssetTypeAction.IsValid())
	{
		FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(AbilityAssetTypeAction.ToSharedRef());
	}
}

//TSharedRef<FMobaAbilityEditorToolKit> FAbilityModule::CreateAbilityEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UMobaAbility* InAbility)
//{
//	//if (!ClassCache.IsValid())
//	//{
//	//	//ClassCache = MakeShareable(new FGraphNodeClassHelper(UAbilityNode::StaticClass()));
//	//	//FGraphNodeClassHelper::AddObservedBlueprintClasses(UEnvQueryGenerator_BlueprintBase::StaticClass());
//	//	//ClassCache->UpdateAvailableBlueprintClasses();
//	//}
//
//	TSharedRef< FMobaAbilityEditorToolKit > NewEnvironmentQueryEditor(new FMobaAbilityEditorToolKit());
//	NewEnvironmentQueryEditor->InitializeAssetEditor(Mode, InitToolkitHost, InAbility);
//	return NewEnvironmentQueryEditor;
//}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAbilityEditorModule, AbilityEditorMode)