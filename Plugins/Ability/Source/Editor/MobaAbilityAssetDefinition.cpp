// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityAssetDefinition.h"
#include "AbilityEditorModule.h"

FText UMobaAbilityAssetDefinition::GetAssetDisplayName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_Ability", "AbilityAsset");
}

FLinearColor UMobaAbilityAssetDefinition::GetAssetColor() const
{
	return FLinearColor::Red; 
}

TSoftClassPtr<UObject> UMobaAbilityAssetDefinition::GetAssetClass() const
{
	return UMobaAbility::StaticClass();
}

TConstArrayView<FAssetCategoryPath> UMobaAbilityAssetDefinition::GetAssetCategories() const
{
	FAssetCategoryPath AssetCategoryPath(FText::FromString("MobaAbility"));
	static const TArray<FAssetCategoryPath, TFixedAllocator<1>> Categories = { AssetCategoryPath };
	return Categories;
}

EAssetCommandResult UMobaAbilityAssetDefinition::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{
	FAbilityEditorModule& AbilityEditorModule = FModuleManager::LoadModuleChecked<FAbilityEditorModule>("AbilityEditor");
	for (UMobaAbility* Ability : OpenArgs.LoadObjects<UMobaAbility>())
	{
		AbilityEditorModule.CreateAbilityEditor(EToolkitMode::Standalone, OpenArgs.ToolkitHost, Ability);
	}
	return EAssetCommandResult::Handled;
}
