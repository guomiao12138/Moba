// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

/**
 * 
 */
//struct FMobaAbilityGraphEditorSummoner : public FDocumentTabFactoryForObjects<UEdGraph>
//{
//	FMobaAbilityGraphEditorSummoner(TSharedPtr<FMobaAbilityEditorToolKit> InHostingApp);
//};


class ABILITY_API FMobaAbilityEditorToolKit final : public FAssetEditorToolkit
{
public:
	virtual FName GetToolkitFName() const override;				// Must implement in derived class!
	virtual FText GetBaseToolkitName() const override;			// Must implement in derived class!
	virtual FString GetWorldCentricTabPrefix() const override;	// Must implement in derived class!
	virtual FLinearColor GetWorldCentricTabColorScale() const override;// Must implement in derived class!
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	//virtual void SaveAsset_Execute() override;



	void InitializeAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* InAssets);

	class UMobaAbilityEdGraphNodeBase* CreateDefaultNode(UEdGraph* ParentGraph, const FVector2D NodeLocation) const;

	void OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection);
	void OnFocused(const TSharedRef<SGraphEditor>& InSGraphEditor);
	FActionMenuContent OnCreateNodeOrPinMenu(UEdGraph* CurrentGraph, const UEdGraphNode* InGraphNode, const UEdGraphPin* InGraphPin, FMenuBuilder* MenuBuilder, bool bIsDebugging);
	FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent);
	void OnNodeSingleClicked(UObject* Obj);
	void OnGraphEditorDropActor(const TArray< TWeakObjectPtr<AActor> >& Actors, UEdGraph* Graph, const FVector2D& DropLocation);
	void OnGraphEditorDropStreamingLevel(const TArray< TWeakObjectPtr<ULevelStreaming> >& Levels, UEdGraph* Graph, const FVector2D& DropLocation);
	void OnNodeDoubleClicked(UEdGraphNode* Node);
	bool OnNodeVerifyTitleCommit(const FText& NewText, UEdGraphNode* NodeBeingChanged, FText& OutErrorMessage);
	void OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged);
	FReply OnSpawnGraphNodeByShortcut(FInputChord InChord, const FVector2D& InPosition, UEdGraph* InGraph);
	void OnNodeSpawnedByKeymap();
	void OnDisallowedPinConnection(const class UEdGraphPin* PinA, const class UEdGraphPin* PinB);
	void NaviagetionDoubleClicked();
	FActionMenuContent OnCreateGraphActionMenu(UEdGraph* InGraph, const FVector2D& InNodePosition, const TArray<UEdGraphPin*>& InDraggedPins, bool bAutoExpand, SGraphEditor::FActionMenuClosed InOnMenuClosed);

	void SetupGraphEditorEvents(UEdGraph* InGraph, SGraphEditor::FGraphEditorEvents& InEvents);

	void Find(const UEdGraphNode* node);


	TSharedPtr<SDockTab> OpenDocument(UObject* DocumentID, FDocumentTracker::EOpenDocumentCause Cause);
private:
	// 生成细节面板
	TSharedRef<SDockTab> SpawnDetailTab(const FSpawnTabArgs& SpawnTabArgs) const;
	TSharedRef<SDockTab> SpawnGraphEdit(const FSpawnTabArgs& SpawnTabArgs);
	TSharedPtr<FWorkspaceItem> WorkSpaceItem;
	TObjectPtr<UEdGraph> EdGraph;

	TSharedPtr<class FDocumentTracker> DocumentManager;
};
