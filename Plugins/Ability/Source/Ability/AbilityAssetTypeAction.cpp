// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityAssetTypeAction.h"
#include "MobaAbility.h"
#include "MobaAbilityEditorToolKit.h"

FAbilityAssetTypeAction::FAbilityAssetTypeAction(EAssetTypeCategories::Type Type)
{
	MyAssetCategory = Type;
}

UClass* FAbilityAssetTypeAction::GetSupportedClass() const
{
	return UMobaAbility::StaticClass();
}

FText FAbilityAssetTypeAction::GetName() const
{
	return  NSLOCTEXT("Editor", "MobaAbility", "MobaAbility");
}

FColor FAbilityAssetTypeAction::GetTypeColor() const
{
	return FColor();
}

uint32 FAbilityAssetTypeAction::GetCategories()
{
	return MyAssetCategory;
}

void FAbilityAssetTypeAction::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	//FAssetTypeActions_Base::OpenAssetEditor(InObjects, EditWithinLevelEditor);

	const EToolkitMode::Type ToolKitModeType = EditWithinLevelEditor ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjectIterator = InObjects.CreateConstIterator(); ObjectIterator; ++ObjectIterator)
	{
		if (UMobaAbility* OurAsset = Cast<UMobaAbility>(*ObjectIterator))
		{
			const TSharedRef<FMobaAbilityEditorToolKit> RecoilAssetEditorToolKit = MakeShareable(new FMobaAbilityEditorToolKit());
			//OurAsset->SetGraph(NewObject<UMobaAbilityEdGraph>(OurAsset));

			RecoilAssetEditorToolKit->InitializeAssetEditor(ToolKitModeType, EditWithinLevelEditor, OurAsset);
		}
	}
}
