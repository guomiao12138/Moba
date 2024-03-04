// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityAssetDefinition.h"

//TConstArrayView<FAssetCategoryPath> UMobaAbilityAssetDefinition::GetAssetCategories() const
//{
//	IAssetTools& AssetToolModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
//	EAssetTypeCategories::Type Category = AssetToolModule.RegisterAdvancedAssetCategory(FName(TEXT("MobaAbility")), NSLOCTEXT("Editor", "MobaAbility", "MobaAbilityAsset"));
//	return Category;
//}

//UMobaAbilityAssetDefinition::UMobaAbilityAssetDefinition()
//{
//}
//
//FText UMobaAbilityAssetDefinition::GetAssetDisplayName() const
//{
//	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_MobaAbility", "MobaAbilityAsset");
//}
//
//TConstArrayView<FAssetCategoryPath> UMobaAbilityAssetDefinition::GetAssetCategories() const
//{
//	FAssetCategoryPath AssetCategoryPath(FText::FromString("MobaAbility"), FText::FromString("MobaAbilityAsset"));
//	static const TArray<FAssetCategoryPath, TFixedAllocator<1>> Categories = { AssetCategoryPath };
//	//static const FAssetCategoryPath Categories[] = { EAssetCategoryPaths::AI };
//	return Categories;
//}
//
//EAssetCommandResult UMobaAbilityAssetDefinition::OpenAssets(const FAssetOpenArgs& OpenArgs) const
//{
//	return Super::OpenAssets(OpenArgs);
//}
