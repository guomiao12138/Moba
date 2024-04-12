// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"



/**
 * This is the module definition for the editor mode. You can implement custom functionality
 * as your plugin module starts up and shuts down. See IModuleInterface for more extensibility options.
 */
class FMobaAbilityEditorToolKit;
class FAbilityAssetTypeAction;
class FAbilityEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;


	void RegisterAssetsAction();

	//virtual TSharedRef<FMobaAbilityEditorToolKit> CreateAbilityEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, class UMobaAbility* InAbility);

	//TSharedPtr<FGraphNodeClassHelper> GetClassCache() { return ClassCache; }

private:
	//TSharedPtr<FGraphNodeClassHelper> ClassCache;
	TSharedPtr<FAbilityAssetTypeAction> AbilityAssetTypeAction;
};
