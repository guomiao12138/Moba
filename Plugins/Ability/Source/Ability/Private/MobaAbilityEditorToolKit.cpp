// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityEditorToolKit.h"

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
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
	WorkSpaceItem = InTabManager->AddLocalWorkspaceMenuCategory(INVTEXT("MobaAbilityEditor"));
	InTabManager->RegisterTabSpawner(FName("MobaAbilityPropertyTab"), FOnSpawnTab::CreateRaw(this, &FMobaAbilityEditorToolKit::SpawnDetailTab))
		.SetGroup(WorkSpaceItem.ToSharedRef())
		.SetDisplayName(INVTEXT("Details"));

	InTabManager->RegisterTabSpawner(FName("MobaAbilityGraphEditorTab"), FOnSpawnTab::CreateLambda([&](const FSpawnTabArgs& SpawnTabArgs)
		{
			return SNew(SDockTab)
				[
					SNew(SGraphEditor).GraphToEdit(EdGraph)
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
	EdGraph = NewObject<UEdGraph>();
	EdGraph->Schema = UEdGraphSchema::StaticClass();
	EdGraph->AddToRoot();


	const TSharedRef<FTabManager::FLayout> StandaloneRecoilAssetLayout = FTabManager::NewLayout("StandaloneMobaAbilityLayout_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
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
