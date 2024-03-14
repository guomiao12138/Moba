// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityEditorToolKit.h"
#include "Node/MobaAbilityEdGraphNodeBase.h"
#include "Node/Schema/MobaAbilityNodeEdGraphSchema.h"
#include "MobaAbility.h"
#include "MobaAbilityEdGraph.h"

#include "WorkflowOrientedApp/WorkflowUObjectDocuments.h"
#include "Framework/Commands/GenericCommands.h"
#include "HAL/PlatformApplicationMisc.h"
#include "Editor/UnrealEd/Public/EdGraphUtilities.h"

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

void FMobaAbilityEditorToolKit::InitializeAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* InAssets)
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
	auto asset = Cast<UMobaAbility>(InAssets);
	if (asset->GetGraph() != nullptr)
	{
		EdGraph = asset->GetGraph();
	}
	else
	{
		UMobaAbilityEdGraph* MobaAbilityEdGraph = NewObject<UMobaAbilityEdGraph>(asset);
		asset->SetGraph(MobaAbilityEdGraph);
		EdGraph = MobaAbilityEdGraph;
		EdGraph->Schema = UMobaAbilityNodeEdGraphSchema::StaticClass();
		const UEdGraphSchema* Schema = EdGraph->GetSchema();
		Schema->CreateDefaultNodesForGraph(*EdGraph);
		//MobaAbilityEdGraph->CreateDefaultNode(TEXT("Start"));
	}

	if (EdGraph)
	{
		EdGraph->AddToRoot();
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString::Printf(TEXT("FMobaAbilityEditorToolKit EdGraph is nullptr"))));
	}


	//UMobaAbilityEdGraphNodeBase* EdGraphNode = CreateNode(EdGraph, { 0, 0 });
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
	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, FName("MobaAbilityEditor"), StandaloneRecoilAssetLayout, true, true, InAssets);
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

UMobaAbilityEdGraphNodeBase* FMobaAbilityEditorToolKit::CreateDefaultNode(UEdGraph* ParentGraph, const FVector2D NodeLocation) const
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
	//InEvents.OnNodeSingleClicked = SGraphEditor::FOnNodeSingleClicked::CreateSP(this, &FMobaAbilityEditorToolKit::OnNodeSingleClicked);
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
	FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
	TArray<UMobaAbilityEdGraphNodeBase*> SubNodes;

	FString ExportedText;

	int32 CopySubNodeIndex = 0;
	for (FGraphPanelSelectionSet::TIterator SelectedIter(SelectedNodes); SelectedIter; ++SelectedIter)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
		UMobaAbilityEdGraphNodeBase* AINode = Cast<UMobaAbilityEdGraphNodeBase>(Node);
		if (Node == nullptr)
		{
			SelectedIter.RemoveCurrent();
			continue;
		}

		Node->PrepareForCopying();

		//if (AINode)
		//{
		//	AINode->CopySubNodeIndex = CopySubNodeIndex;

		//	// append all subnodes for selection
		//	for (int32 Idx = 0; Idx < AINode->SubNodes.Num(); Idx++)
		//	{
		//		AINode->SubNodes[Idx]->CopySubNodeIndex = CopySubNodeIndex;
		//		SubNodes.Add(AINode->SubNodes[Idx]);
		//	}

		//	CopySubNodeIndex++;
		//}
	}

	for (int32 Idx = 0; Idx < SubNodes.Num(); Idx++)
	{
		SelectedNodes.Add(SubNodes[Idx]);
		SubNodes[Idx]->PrepareForCopying();
	}

	//FEdGraphUtilities::ExportNodesToText(SelectedNodes, ExportedText);
	//FPlatformApplicationMisc::ClipboardCopy(*ExportedText);

	//for (FGraphPanelSelectionSet::TIterator SelectedIter(SelectedNodes); SelectedIter; ++SelectedIter)
	//{
	//	UMobaAbilityEdGraphNodeBase* Node = Cast<UMobaAbilityEdGraphNodeBase>(*SelectedIter);
	//	if (Node)
	//	{
	//		Node->PostCopyNode();
	//	}
	//}
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
	//TSharedPtr<SGraphEditor> CurrentGraphEditor = UpdateGraphEdPtr.Pin();
	//if (!CurrentGraphEditor.IsValid())
	//{
	//	return;
	//}

	//// Undo/Redo support
	//const FScopedTransaction Transaction(FGenericCommands::Get().Paste->GetDescription());
	//UEdGraph* EdGraph = CurrentGraphEditor->GetCurrentGraph();
	//UAIGraph* AIGraph = Cast<UAIGraph>(EdGraph);

	//EdGraph->Modify();
	//if (AIGraph)
	//{
	//	AIGraph->LockUpdates();
	//}

	//UAIGraphNode* SelectedParent = NULL;
	//bool bHasMultipleNodesSelected = false;

	//const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
	//for (FGraphPanelSelectionSet::TConstIterator SelectedIter(SelectedNodes); SelectedIter; ++SelectedIter)
	//{
	//	UAIGraphNode* Node = Cast<UAIGraphNode>(*SelectedIter);
	//	if (Node && Node->IsSubNode())
	//	{
	//		Node = Node->ParentNode;
	//	}

	//	if (Node)
	//	{
	//		if (SelectedParent == nullptr)
	//		{
	//			SelectedParent = Node;
	//		}
	//		else
	//		{
	//			bHasMultipleNodesSelected = true;
	//			break;
	//		}
	//	}
	//}

	//// Clear the selection set (newly pasted stuff will be selected)
	//CurrentGraphEditor->ClearSelectionSet();

	//// Grab the text to paste from the clipboard.
	//FString TextToImport;
	//FPlatformApplicationMisc::ClipboardPaste(TextToImport);

	//// Import the nodes
	//TSet<UEdGraphNode*> PastedNodes;
	//FEdGraphUtilities::ImportNodesFromText(EdGraph, TextToImport, /*out*/ PastedNodes);

	////Average position of nodes so we can move them while still maintaining relative distances to each other
	//FVector2D AvgNodePosition(0.0f, 0.0f);

	//// Number of nodes used to calculate AvgNodePosition
	//int32 AvgCount = 0;

	//for (TSet<UEdGraphNode*>::TIterator It(PastedNodes); It; ++It)
	//{
	//	UEdGraphNode* EdNode = *It;
	//	UAIGraphNode* AINode = Cast<UAIGraphNode>(EdNode);
	//	if (EdNode && (AINode == nullptr || !AINode->IsSubNode()))
	//	{
	//		AvgNodePosition.X += EdNode->NodePosX;
	//		AvgNodePosition.Y += EdNode->NodePosY;
	//		++AvgCount;
	//	}
	//}

	//if (AvgCount > 0)
	//{
	//	float InvNumNodes = 1.0f / float(AvgCount);
	//	AvgNodePosition.X *= InvNumNodes;
	//	AvgNodePosition.Y *= InvNumNodes;
	//}

	//bool bPastedParentNode = false;

	//TMap<FGuid/*New*/, FGuid/*Old*/> NewToOldNodeMapping;

	//TMap<int32, UAIGraphNode*> ParentMap;
	//for (TSet<UEdGraphNode*>::TIterator It(PastedNodes); It; ++It)
	//{
	//	UEdGraphNode* PasteNode = *It;
	//	UAIGraphNode* PasteAINode = Cast<UAIGraphNode>(PasteNode);

	//	if (PasteNode && (PasteAINode == nullptr || !PasteAINode->IsSubNode()))
	//	{
	//		bPastedParentNode = true;

	//		// Select the newly pasted stuff
	//		CurrentGraphEditor->SetNodeSelection(PasteNode, true);

	//		const FVector::FReal NodePosX = (PasteNode->NodePosX - AvgNodePosition.X) + Location.X;
	//		const FVector::FReal NodePosY = (PasteNode->NodePosY - AvgNodePosition.Y) + Location.Y;

	//		PasteNode->NodePosX = static_cast<int32>(NodePosX);
	//		PasteNode->NodePosY = static_cast<int32>(NodePosY);

	//		PasteNode->SnapToGrid(16);

	//		const FGuid OldGuid = PasteNode->NodeGuid;

	//		// Give new node a different Guid from the old one
	//		PasteNode->CreateNewGuid();

	//		const FGuid NewGuid = PasteNode->NodeGuid;

	//		NewToOldNodeMapping.Add(NewGuid, OldGuid);

	//		if (PasteAINode)
	//		{
	//			PasteAINode->RemoveAllSubNodes();
	//			ParentMap.Add(PasteAINode->CopySubNodeIndex, PasteAINode);
	//		}
	//	}
	//}

	//for (TSet<UEdGraphNode*>::TIterator It(PastedNodes); It; ++It)
	//{
	//	UAIGraphNode* PasteNode = Cast<UAIGraphNode>(*It);
	//	if (PasteNode && PasteNode->IsSubNode())
	//	{
	//		PasteNode->NodePosX = 0;
	//		PasteNode->NodePosY = 0;

	//		// remove subnode from graph, it will be referenced from parent node
	//		PasteNode->DestroyNode();

	//		PasteNode->ParentNode = ParentMap.FindRef(PasteNode->CopySubNodeIndex);
	//		if (PasteNode->ParentNode)
	//		{
	//			PasteNode->ParentNode->AddSubNode(PasteNode, EdGraph);
	//		}
	//		else if (!bHasMultipleNodesSelected && !bPastedParentNode && SelectedParent)
	//		{
	//			PasteNode->ParentNode = SelectedParent;
	//			SelectedParent->AddSubNode(PasteNode, EdGraph);
	//		}
	//	}
	//}

	//FixupPastedNodes(PastedNodes, NewToOldNodeMapping);

	//if (AIGraph)
	//{
	//	AIGraph->UpdateClassData();
	//	AIGraph->OnNodesPasted(TextToImport);
	//	AIGraph->UnlockUpdates();
	//}

	//// Update UI
	//CurrentGraphEditor->NotifyGraphChanged();

	//UObject* GraphOwner = EdGraph->GetOuter();
	//if (GraphOwner)
	//{
	//	GraphOwner->PostEditChange();
	//	GraphOwner->MarkPackageDirty();
	//}
}

bool FMobaAbilityEditorToolKit::CanCutSelected()
{
	return false;
}

void FMobaAbilityEditorToolKit::CutSelected()
{
}

bool FMobaAbilityEditorToolKit::CanDuplicateSelected()
{
	return false;
}

void FMobaAbilityEditorToolKit::DuplicateSelected()
{
}



