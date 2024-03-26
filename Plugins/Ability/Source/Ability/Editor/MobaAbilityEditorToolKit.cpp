// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityEditorToolKit.h"
#include "Node/AbilityNode.h"
#include "Node/Schema/MobaAbilityNodeEdGraphSchema.h"
#include "Ability/Runtime/MobaAbility.h"
#include "MobaAbilityEdGraph.h"

#include "WorkflowOrientedApp/WorkflowUObjectDocuments.h"
#include "Framework/Commands/GenericCommands.h"
#include "HAL/PlatformApplicationMisc.h"
#include "Editor/UnrealEd/Public/EdGraphUtilities.h"
#include "Editor/GraphEditor/Public/SNodePanel.h"

#include "IDetailsView.h"

void FMobaAbilityEditorToolKit::PostUndo(bool bSuccess)
{
}

void FMobaAbilityEditorToolKit::PostRedo(bool bSuccess)
{
}

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
	CreateUICommandList();

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
	WorkSpaceItem = InTabManager->AddLocalWorkspaceMenuCategory(INVTEXT("MobaAbilityEditor"));
	InTabManager->RegisterTabSpawner(FName("MobaAbilityPropertyTab"), FOnSpawnTab::CreateRaw(this, &FMobaAbilityEditorToolKit::SpawnDetailTab))
		.SetGroup(WorkSpaceItem.ToSharedRef())
		.SetDisplayName(INVTEXT("Details"));


	InTabManager->RegisterTabSpawner(FName("MobaAbilityGraphEditorTab"), FOnSpawnTab::CreateSP(this, &FMobaAbilityEditorToolKit::SpawnGraphEdit))
		.SetGroup(WorkSpaceItem.ToSharedRef())
		.SetDisplayName(INVTEXT("MobaAbilityGraph"));
}

void FMobaAbilityEditorToolKit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	InTabManager->UnregisterTabSpawner(FName("MobaAbilityPropertyTab"));
	InTabManager->UnregisterTabSpawner(FName("MobaAbilityGraphEditorTab"));
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
}

//void FMobaAbilityEditorToolKit::SaveAsset_Execute()
//{
//
//	FAssetEditorToolkit::SaveAsset_Execute();
//
//}

void FMobaAbilityEditorToolKit::InitializeAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UMobaAbility* InAsset)
{

	//DocumentManager = MakeShareable(new FDocumentTracker);
	//bCheckDirtyOnAssetSave = true;

	//if (!DocumentManager.IsValid())
	//{
	//	DocumentManager = MakeShareable(new FDocumentTracker);
	//	DocumentManager->Initialize(SharedThis(this));

	//	{

	//		TSharedRef<FDocumentTabFactory> GraphEditorFactory = MakeShared<FMobaAbilityGraphEditorSummoner>(SharedThis(this));

	//		DocumentManager->RegisterDocumentFactory(GraphEditorFactory);
	//	}
	//}
	if (InAsset->Graph != nullptr)
	{
		EdGraph = InAsset->Graph;
	}
	else
	{
		UMobaAbilityEdGraph* MobaAbilityEdGraph = NewObject<UMobaAbilityEdGraph>(InAsset);
		InAsset->Graph = MobaAbilityEdGraph;
		EdGraph = MobaAbilityEdGraph;
		EdGraph->Schema = UMobaAbilityNodeEdGraphSchema::StaticClass();
		const UEdGraphSchema* Schema = EdGraph->GetSchema();
		Schema->CreateDefaultNodesForGraph(*MobaAbilityEdGraph);
		//MobaAbilityEdGraph->CreateDefaultNode(TEXT("Start"));
	}

	if (EdGraph)
	{
		EdGraph->AddToRoot();
	}
	else
	{
		FMessageDialog::Open(EAppMsgCategory::Error, EAppMsgType::Ok, FText::FromString(FString::Printf(TEXT("FMobaAbilityEditorToolKit EdGraph is nullptr"))));
	}


	//UAbilityNode* EdGraphNode = CreateNode(EdGraph, { 0, 0 });
	//EdGraph->AddNode(EdGraphNode);
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
	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, FName("MobaAbilityEditor"), StandaloneRecoilAssetLayout, true, true, InAsset);
	//InitAssetEditor(Mode, InitToolkitHost, FName("MobaAbilityEditor"), StandaloneRecoilAssetLayout, true, true, InAssets);
	RegenerateMenusAndToolbars();

}

void FMobaAbilityEditorToolKit::CreateUICommandList()
{
	GraphEditorCommands = MakeShared<FUICommandList>();

	GraphEditorCommands->MapAction(FGenericCommands::Get().Delete,
		FExecuteAction::CreateSP(this, &FMobaAbilityEditorToolKit::DeleteSelected),
		FCanExecuteAction::CreateSP(this, &FMobaAbilityEditorToolKit::CanDeleteSelected)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Copy,
		FExecuteAction::CreateSP(this, &FMobaAbilityEditorToolKit::CopySelected),
		FCanExecuteAction::CreateSP(this, &FMobaAbilityEditorToolKit::CanCopySelected)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Cut,
		FExecuteAction::CreateSP(this, &FMobaAbilityEditorToolKit::CutSelected),
		FCanExecuteAction::CreateSP(this, &FMobaAbilityEditorToolKit::CanCutSelected)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Paste,
		FExecuteAction::CreateSP(this, &FMobaAbilityEditorToolKit::Paste),
		FCanExecuteAction::CreateSP(this, &FMobaAbilityEditorToolKit::CanPaste)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Duplicate,
		FExecuteAction::CreateSP(this, &FMobaAbilityEditorToolKit::DuplicateSelected),
		FCanExecuteAction::CreateSP(this, &FMobaAbilityEditorToolKit::CanDuplicateSelected)
	);

}

UAbilityNode* FMobaAbilityEditorToolKit::CreateDefaultNode(UEdGraph* ParentGraph, const FVector2D NodeLocation) const
{
	check(ParentGraph != nullptr)
	UAbilityNode* ResultGraphNode = NewObject<UAbilityNode>(ParentGraph);
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
	if (NewSelection.Num() > 0)
	{
		/*GraphEditor*/
	}
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
	if (auto node = GraphEditor.Get()->GetSingleSelectedNode())
	{
		OnNodeSingleClicked(node);
	}
	else
	{
		DetailsView->SetObject(GetEditingObject());
	}
	return FReply::Handled();
}

void FMobaAbilityEditorToolKit::OnNodeSingleClicked(UObject* Obj)
{
	DetailsView->SetObject(Obj);
}

void FMobaAbilityEditorToolKit::OnGraphEditorDropActor(const TArray<TWeakObjectPtr<AActor>>& Actors, UEdGraph* Graph, const FVector2D& DropLocation)
{
}

void FMobaAbilityEditorToolKit::OnGraphEditorDropStreamingLevel(const TArray<TWeakObjectPtr<ULevelStreaming>>& Levels, UEdGraph* Graph, const FVector2D& DropLocation)
{
}

void FMobaAbilityEditorToolKit::OnNodeDoubleClicked(UEdGraphNode* Node)
{
	if (Node && Node->CanJumpToDefinition())
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

TSharedRef<SDockTab> FMobaAbilityEditorToolKit::SpawnDetailTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::Get().LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	const FDetailsViewArgs DetailsViewArgs;

	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(GetEditingObject());
	return SNew(SDockTab)
		[
			DetailsView.ToSharedRef()
		];
}

TSharedRef<SDockTab> FMobaAbilityEditorToolKit::SpawnGraphEdit(const FSpawnTabArgs& SpawnTabArgs)
{
	SGraphEditor::FGraphEditorEvents InEvents;
	//InEvents.OnDoubleClicked = SGraphEditor::FOnDoubleClicked::CreateSP(this, &FMobaAbilityEditorToolKit::NaviagetionDoubleClicked);
	SetupGraphEditorEvents(EdGraph, InEvents);

	GraphEditor = SNew(SGraphEditor)
		.AdditionalCommands(GraphEditorCommands)
		.GraphToEdit(EdGraph)
		.GraphEvents(InEvents)
		.AssetEditorToolkit(this->AsShared());

	return SNew(SDockTab)
		[
			GraphEditor.ToSharedRef()
		];
}


void FMobaAbilityEditorToolKit::SetupGraphEditorEvents(UEdGraph* InGraph, SGraphEditor::FGraphEditorEvents& InEvents)
{
	InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &FMobaAbilityEditorToolKit::OnSelectedNodesChanged);
	//InEvents.OnFocused = SGraphEditor::FOnFocused::CreateSP(this, &FMobaAbilityEditorToolKit::OnFocused);
	//InEvents.OnCreateNodeOrPinMenu = SGraphEditor::FOnCreateNodeOrPinMenu::CreateSP(this, &FMobaAbilityEditorToolKit::OnCreateNodeOrPinMenu);
	//InEvents.OnMouseButtonDown = SGraphEditor::FOnMouseButtonDown::CreateSP(this, &FMobaAbilityEditorToolKit::OnMouseButtonDown);
	InEvents.OnNodeSingleClicked = SGraphEditor::FOnNodeSingleClicked::CreateSP(this, &FMobaAbilityEditorToolKit::OnNodeSingleClicked);
	//InEvents.OnDropActor = SGraphEditor::FOnDropActor::CreateSP(this, &FMobaAbilityEditorToolKit::OnGraphEditorDropActor);
	//InEvents.OnDropStreamingLevel = SGraphEditor::FOnDropStreamingLevel::CreateSP(this, &FMobaAbilityEditorToolKit::OnGraphEditorDropStreamingLevel);
	InEvents.OnNodeDoubleClicked = FSingleNodeEvent::CreateSP(this, &FMobaAbilityEditorToolKit::OnNodeDoubleClicked);
	//InEvents.OnVerifyTextCommit = FOnNodeVerifyTextCommit::CreateSP(this, &FMobaAbilityEditorToolKit::OnNodeVerifyTitleCommit);
	//InEvents.OnTextCommitted = FOnNodeTextCommitted::CreateSP(this, &FMobaAbilityEditorToolKit::OnNodeTitleCommitted);
	//InEvents.OnSpawnNodeByShortcut = SGraphEditor::FOnSpawnNodeByShortcut::CreateSP(this, &FMobaAbilityEditorToolKit::OnSpawnGraphNodeByShortcut, InGraph);
	//InEvents.OnNodeSpawnedByKeymap = SGraphEditor::FOnNodeSpawnedByKeymap::CreateSP(this, &FMobaAbilityEditorToolKit::OnNodeSpawnedByKeymap);
	//InEvents.OnDisallowedPinConnection = SGraphEditor::FOnDisallowedPinConnection::CreateSP(this, &FMobaAbilityEditorToolKit::OnDisallowedPinConnection);
	//InEvents.OnDoubleClicked = SGraphEditor::FOnDoubleClicked::CreateSP(this, &FMobaAbilityEditorToolKit::NaviagetionDoubleClicked);
	//InEvents.OnCreateActionMenu = SGraphEditor::FOnCreateActionMenu::CreateSP(this, &FMobaAbilityEditorToolKit::OnCreateGraphActionMenu);

	// Custom menu for K2 schemas
	//if (InGraph->Schema != nullptr && InGraph->Schema->IsChildOf(UEdGraphSchema_K2::StaticClass()))
	//{
	//}
}

FGraphPanelSelectionSet FMobaAbilityEditorToolKit::GetSelectedNodes() const
{
	return GraphEditor->GetSelectedNodes();
}

bool FMobaAbilityEditorToolKit::CanDeleteSelected()
{
	// If any of the nodes can be deleted then we should allow deleting
	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
	for (FGraphPanelSelectionSet::TConstIterator SelectedIter(SelectedNodes); SelectedIter; ++SelectedIter)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
		if (Node && Node->CanUserDeleteNode())
		{
			return true;
		}
	}

	return false;
}

void FMobaAbilityEditorToolKit::DeleteSelected()
{
	const FScopedTransaction Transaction(FGenericCommands::Get().Delete->GetDescription());
	GraphEditor->GetCurrentGraph()->Modify();
	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();

	for (FGraphPanelSelectionSet::TConstIterator NodeIt(SelectedNodes); NodeIt; ++NodeIt)
	{
		if (UEdGraphNode* Node = Cast<UEdGraphNode>(*NodeIt))
		{
			if (Node->CanUserDeleteNode())
			{
				Node->Modify();
				Node->DestroyNode();
			}
		}
	}

	GraphEditor->ClearSelectionSet();
}

bool FMobaAbilityEditorToolKit::CanCopySelected()
{
	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
	for (FGraphPanelSelectionSet::TConstIterator SelectedIter(SelectedNodes); SelectedIter; ++SelectedIter)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
		if (Node && Node->CanDuplicateNode())
		{
			return true;
		}
	}

	return false;
}

void FMobaAbilityEditorToolKit::CopySelected()
{
	// Export the selected nodes and place the text on the clipboard
	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();

	FString ExportedText;

	for (FGraphPanelSelectionSet::TConstIterator SelectedIter(SelectedNodes); SelectedIter; ++SelectedIter)
	{
		if (UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter))
		{
			Node->PrepareForCopying();
		}
	}

	FEdGraphUtilities::ExportNodesToText(SelectedNodes, /*out*/ ExportedText);
	FPlatformApplicationMisc::ClipboardCopy(*ExportedText);
}

bool FMobaAbilityEditorToolKit::CanPaste()
{
	//TSharedPtr<SGraphEditor> CurrentGraphEditor = UpdateGraphEdPtr.Pin();
	//if (!CurrentGraphEditor.IsValid())
	//{
	//	return false;
	//}

	FString ClipboardContent;
	FPlatformApplicationMisc::ClipboardPaste(ClipboardContent);

	return FEdGraphUtilities::CanImportNodesFromText(EdGraph, ClipboardContent);
}

void FMobaAbilityEditorToolKit::Paste()
{
	if (GraphEditor)
	{
		PasteNodesHere(GraphEditor->GetPasteLocation());
	}
}

void FMobaAbilityEditorToolKit::PasteNodesHere(const FVector2D& Location)
{
	// Find the graph editor with focus
	//TSharedPtr<SGraphEditor> FocusedGraphEd = FocusedGraphEdPtr.Pin();
	//if (!FocusedGraphEd.IsValid())
	//{
	//	return;
	//}
	// Select the newly pasted stuff
	bool bNeedToModifyStructurally = false;
	{
		const FScopedTransaction Transaction(FGenericCommands::Get().Paste->GetDescription());
		EdGraph->Modify();

		// Clear the selection set (newly pasted stuff will be selected)
		//SetUISelectionState(NAME_None);

		// Grab the text to paste from the clipboard.
		FString TextToImport;
		FPlatformApplicationMisc::ClipboardPaste(TextToImport);

		// Import the nodes
		TSet<UEdGraphNode*> PastedNodes;
		FEdGraphUtilities::ImportNodesFromText(EdGraph, TextToImport, /*out*/ PastedNodes);

		FVector2D AvgNodePosition(0.0f, 0.0f);

		for (TSet<UEdGraphNode*>::TIterator It(PastedNodes); It; ++It)
		{
			UEdGraphNode* Node = *It;
			AvgNodePosition.X += Node->NodePosX;
			AvgNodePosition.Y += Node->NodePosY;
		}

		float InvNumNodes = 1.0f / float(PastedNodes.Num());
		AvgNodePosition.X *= InvNumNodes;
		AvgNodePosition.Y *= InvNumNodes;

		TSet<FString> NamespacesToImport;

		for (TSet<UEdGraphNode*>::TIterator It(PastedNodes); It; ++It)
		{
			UEdGraphNode* Node = *It;
			GraphEditor->SetNodeSelection(Node, true);

			Node->NodePosX = static_cast<int32>((Node->NodePosX - AvgNodePosition.X) + Location.X);
			Node->NodePosY = static_cast<int32>((Node->NodePosY - AvgNodePosition.Y) + Location.Y);

			Node->SnapToGrid(SNodePanel::GetSnapGridSize());

			Node->CreateNewGuid();
		}
	}
	// Update UI
	GraphEditor->NotifyGraphChanged();
}

bool FMobaAbilityEditorToolKit::CanCutSelected()
{
	return CanCopySelected() && CanDeleteSelected();
}

void FMobaAbilityEditorToolKit::CutSelected()
{
	CopySelected();
	DeleteSelectedDuplicatableNodes();
}

bool FMobaAbilityEditorToolKit::CanDuplicateSelected()
{
	return CanCopySelected();
}

void FMobaAbilityEditorToolKit::DuplicateSelected()
{
	CopySelected();
	Paste();
}


void FMobaAbilityEditorToolKit::DeleteSelectedDuplicatableNodes()
{
	// Cache off the old selection
	const FGraphPanelSelectionSet OldSelectedNodes = GetSelectedNodes();

	// Clear the selection and only select the nodes that can be duplicated
	FGraphPanelSelectionSet CurrentSelection;
	//TSharedPtr<SGraphEditor> FocusedGraphEd = FocusedGraphEdPtr.Pin();
	if (GraphEditor)
	{
		GraphEditor->ClearSelectionSet();

		FGraphPanelSelectionSet RemainingNodes;
		for (FGraphPanelSelectionSet::TConstIterator SelectedIter(OldSelectedNodes); SelectedIter; ++SelectedIter)
		{
			UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
			if ((Node != nullptr) && Node->CanDuplicateNode())
			{
				GraphEditor->SetNodeSelection(Node, true);
			}
			else
			{
				RemainingNodes.Add(Node);
			}
		}

		// Delete the duplicatable nodes
		DeleteSelected();

		// Reselect whatever's left from the original selection after the deletion
		GraphEditor->ClearSelectionSet();

		for (FGraphPanelSelectionSet::TConstIterator SelectedIter(RemainingNodes); SelectedIter; ++SelectedIter)
		{
			if (UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter))
			{
				GraphEditor->SetNodeSelection(Node, true);
			}
		}
	}
}



