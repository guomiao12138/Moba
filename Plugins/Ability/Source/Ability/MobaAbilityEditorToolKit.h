// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

/**
 * 
 */
class ABILITY_API FMobaAbilityEditorToolKit final : public FAssetEditorToolkit
{
public:
	virtual FName GetToolkitFName() const override;				// Must implement in derived class!
	virtual FText GetBaseToolkitName() const override;			// Must implement in derived class!
	virtual FString GetWorldCentricTabPrefix() const override;	// Must implement in derived class!
	virtual FLinearColor GetWorldCentricTabColorScale() const override;// Must implement in derived class!
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	void InitializeAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* InAssets);

	class UMobaAbilityEdGraphNodeBase* CreateNode(UEdGraph* ParentGraph, const FVector2D NodeLocation) const;

private:
	// 生成细节面板
	TSharedRef<SDockTab> SpawnDetailTab(const FSpawnTabArgs& SpawnTabArgs) const;
	TSharedRef<SDockTab> SpawnGraphEdit(const FSpawnTabArgs& SpawnTabArgs) const;
	TSharedPtr<FWorkspaceItem> WorkSpaceItem;
	TObjectPtr<UEdGraph> EdGraph;
};
