// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityEditorToolKit.h"
#include "Node/MobaAbilityEdGraphNodeBase.h"
#include "Node/Schema/MobaAbilityNodeEdGraphSchema.h"
#include "MobaAbility.h"
#include "MobaAbilityEdGraph.h"

FName FMobaAbilityEditorToolKit::GetToolkitFName() const
{
	return FName("MobaAssetEditorToolkit");
}

FText FMobaAbilityEditorToolKit::GetBaseToolkitName() const
{
	return NSLOCTEXT("EditorExtension", "MobaAbility Toolkit Name", "Moba技能编辑器");
}

FString FMobaAbilityEditorToolKit::GetWorldCentricTabPrefix() const
{
	return NSLOCTEXT("EditorExtension", "MobaAbility Toolkit Name", "Moba技能编辑器").ToString();
}

FLinearColor FMobaAbilityEditorToolKit::GetWorldCentricTabColorScale() const
{
	return FLinearColor::Red;
}

void FMobaAbilityEditorToolKit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	SGraphEditor::FGraphEditorEvents InEvents;
	//InEvents.OnDoubleClicked = SGraphEditor::FOnDoubleClicked::CreateSP(this, &FMobaAbilityEditorToolKit::NaviagetionDoubleClicked);
	SetupGraphEditorEvents(EdGraph, InEvents);
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
	WorkSpaceItem = InTabManager->AddLocalWorkspaceMenuCategory(INVTEXT("MobaAbilityEditor"));
	InTabManager->RegisterTabSpawner(FName("MobaAbilityPropertyTab"), FOnSpawnTab::CreateRaw(this, &FMobaAbilityEditorToolKit::SpawnDetailTab))
		.SetGroup(WorkSpaceItem.ToSharedRef())
		.SetDisplayName(INVTEXT("Details"));


	InTabManager->RegisterTabSpawner(FName("MobaAbilityGraphEditorTab"), FOnSpawnTab::CreateLambda([&](const FSpawnTabArgs& SpawnTabArgs)
		{
			return SNew(SDockTab)
				[
					SNew(SGraphEditor)
						.GraphToEdit(EdGraph)
						.GraphEvents(InEvents)
				];
		}))
		.SetGroup(WorkSpaceItem.ToSharedRef())
		.SetDisplayName(INVTEXT("MobaAbilityGraph"));
}

void FMobaAbilityEditorToolKit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	InTabManager->UnregisterTabSpawner(FName("MobaAbilityPropertyTab"));
	InTabManager->UnregisterTabSpawner(FName("MobaAbilityGraphEditorTab"));
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
}

void FMobaAbilityEditorToolKit::InitializeAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* InAssets)
{
	UMobaAbilityEdGraph* graph = NewObject<UMobaAbilityEdGraph>();
	Cast<UMobaAbility>(InAssets)->SetGraph(graph);
	EdGraph = graph;
	EdGraph->Schema = UMobaAbilityNodeEdGraphSchema::StaticClass();
	EdGraph->AddToRoot();

	UMobaAbilityEdGraphNodeBase* EdGraphNode = CreateNode(EdGraph, { 0, 0 });
	EdGraph->AddNode(EdGraphNode);

	const TSharedRef<FTabManager::FLayout> StandaloneRecoilAssetLayout = FTabManager::NewLayout("StandaloneMobaAbilityLayout_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split(
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.7)
					->AddTab(FName("MobaAbilityGraphEditorTab"), ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.3)
					->AddTab(FName("MobaAbilityPropertyTab"), ETabState::OpenedTab)
				)
			)
		);
	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, FName("MobaAbilityEditor"), StandaloneRecoilAssetLayout, true, true, InAssets);
	//InitAssetEditor(Mode, InitToolkitHost, FName("MobaAbilityEditor"), StandaloneRecoilAssetLayout, true, true, InAssets);
	//RegenerateMenusAndToolbars();
}

UMobaAbilityEdGraphNodeBase* FMobaAbilityEditorToolKit::CreateNode(UEdGraph* ParentGraph, const FVector2D NodeLocation) const
{
	check(ParentGraph != nullptr)
	UMobaAbilityEdGraphNodeBase* ResultGraphNode = NewObject<UMobaAbilityEdGraphNodeBase>(ParentGraph);
	ParentGraph->Modify();
	ResultGraphNode->SetFlags(RF_Transactional);

	ResultGraphNode->Rename(nullptr, ParentGraph, REN_NonTransactional);
	ResultGraphNode->CreateNewGuid();
	ResultGraphNode->NodePosX = NodeLocation.X;
	ResultGraphNode->NodePosY = NodeLocation.Y;

	ResultGraphNode->AllocateDefaultPins();
	return ResultGraphNode;
}

void FMobaAbilityEditorToolKit::OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection)
{
}

void FMobaAbilityEditorToolKit::OnFocused(const TSharedRef<SGraphEditor>& InSGraphEditor)
{
}

FActionMenuContent FMobaAbilityEditorToolKit::OnCreateNodeOrPinMenu(UEdGraph* CurrentGraph, const UEdGraphNode* InGraphNode, const UEdGraphPin* InGraphPin, FMenuBuilder* MenuBuilder, bool bIsDebugging)
{
	return FActionMenuContent();
}

FReply FMobaAbilityEditorToolKit::OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent)
{
	return FReply::Handled();
}

void FMobaAbilityEditorToolKit::OnNodeSingleClicked(UObject* Obj)
{
}

void FMobaAbilityEditorToolKit::OnGraphEditorDropActor(const TArray<TWeakObjectPtr<AActor>>& Actors, UEdGraph* Graph, const FVector2D& DropLocation)
{
}

void FMobaAbilityEditorToolKit::OnGraphEditorDropStreamingLevel(const TArray<TWeakObjectPtr<ULevelStreaming>>& Levels, UEdGraph* Graph, const FVector2D& DropLocation)
{
}

void FMobaAbilityEditorToolKit::OnNodeDoubleClicked(UEdGraphNode* Node)
{
	if (Node->CanJumpToDefinition())
	{
		Node->JumpToDefinition();
	}
}

bool FMobaAbilityEditorToolKit::OnNodeVerifyTitleCommit(const FText& NewText, UEdGraphNode* NodeBeingChanged, FText& OutErrorMessage)
{
	return false;
}

void FMobaAbilityEditorToolKit::OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged)
{
}

FReply FMobaAbilityEditorToolKit::OnSpawnGraphNodeByShortcut(FInputChord InChord, const FVector2D& InPosition, UEdGraph* InGraph)
{
	return FReply::Handled();
}

void FMobaAbilityEditorToolKit::OnNodeSpawnedByKeymap()
{
}

void FMobaAbilityEditorToolKit::OnDisallowedPinConnection(const class UEdGraphPin* PinA, const class UEdGraphPin* PinB)
{
}

void FMobaAbilityEditorToolKit::NaviagetionDoubleClicked()
{
}

FActionMenuContent FMobaAbilityEditorToolKit::OnCreateGraphActionMenu(UEdGraph* InGraph, const FVector2D& InNodePosition, const TArray<UEdGraphPin*>& InDraggedPins, bool bAutoExpand, SGraphEditor::FActionMenuClosed InOnMenuClosed)
{
	return FActionMenuContent();
}

TSharedRef<SDockTab> FMobaAbilityEditorToolKit::SpawnDetailTab(const FSpawnTabArgs& SpawnTabArgs) const
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::Get().LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	const FDetailsViewArgs DetailsViewArgs;

	const TSharedRef<IDetailsView> AssetPropertyView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	AssetPropertyView->SetObject(GetEditingObject());
	return SNew(SDockTab)
	[
		AssetPropertyView
	];
}

TSharedRef<SDockTab> FMobaAbilityEditorToolKit::SpawnGraphEdit(const FSpawnTabArgs& SpawnTabArgs) const
{
	return SNew(SDockTab)
		[
			SNew(SGraphEditor).GraphToEdit(EdGraph)
		];
}


void FMobaAbilityEditorToolKit::SetupGraphEditorEvents(UEdGraph* InGraph, SGraphEditor::FGraphEditorEvents& InEvents)
{
	InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &FMobaAbilityEditorToolKit::OnSelectedNodesChanged);
	InEvents.OnFocused = SGraphEditor::FOnFocused::CreateSP(this, &FMobaAbilityEditorToolKit::OnFocused);
	InEvents.OnCreateNodeOrPinMenu = SGraphEditor::FOnCreateNodeOrPinMenu::CreateSP(this, &FMobaAbilityEditorToolKit::OnCreateNodeOrPinMenu);
	InEvents.OnMouseButtonDown = SGraphEditor::FOnMouseButtonDown::CreateSP(this, &FMobaAbilityEditorToolKit::OnMouseButtonDown);
	InEvents.OnNodeSingleClicked = SGraphEditor::FOnNodeSingleClicked::CreateSP(this, &FMobaAbilityEditorToolKit::OnNodeSingleClicked);
	InEvents.OnDropActor = SGraphEditor::FOnDropActor::CreateSP(this, &FMobaAbilityEditorToolKit::OnGraphEditorDropActor);
	InEvents.OnDropStreamingLevel = SGraphEditor::FOnDropStreamingLevel::CreateSP(this, &FMobaAbilityEditorToolKit::OnGraphEditorDropStreamingLevel);
	InEvents.OnNodeDoubleClicked = FSingleNodeEvent::CreateSP(this, &FMobaAbilityEditorToolKit::OnNodeDoubleClicked);
	InEvents.OnVerifyTextCommit = FOnNodeVerifyTextCommit::CreateSP(this, &FMobaAbilityEditorToolKit::OnNodeVerifyTitleCommit);
	InEvents.OnTextCommitted = FOnNodeTextCommitted::CreateSP(this, &FMobaAbilityEditorToolKit::OnNodeTitleCommitted);
	InEvents.OnSpawnNodeByShortcut = SGraphEditor::FOnSpawnNodeByShortcut::CreateSP(this, &FMobaAbilityEditorToolKit::OnSpawnGraphNodeByShortcut, InGraph);
	InEvents.OnNodeSpawnedByKeymap = SGraphEditor::FOnNodeSpawnedByKeymap::CreateSP(this, &FMobaAbilityEditorToolKit::OnNodeSpawnedByKeymap);
	InEvents.OnDisallowedPinConnection = SGraphEditor::FOnDisallowedPinConnection::CreateSP(this, &FMobaAbilityEditorToolKit::OnDisallowedPinConnection);
	InEvents.OnDoubleClicked = SGraphEditor::FOnDoubleClicked::CreateSP(this, &FMobaAbilityEditorToolKit::NaviagetionDoubleClicked);
	InEvents.OnCreateActionMenu = SGraphEditor::FOnCreateActionMenu::CreateSP(this, &FMobaAbilityEditorToolKit::OnCreateGraphActionMenu);

	// Custom menu for K2 schemas
	if (InGraph->Schema != nullptr && InGraph->Schema->IsChildOf(UEdGraphSchema_K2::StaticClass()))
	{
	}
}