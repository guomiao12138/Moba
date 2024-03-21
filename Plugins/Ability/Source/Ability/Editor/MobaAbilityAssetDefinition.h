// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetDefinitionDefault.h"
#include "MobaAbility.h"
#include "MobaAbilityAssetDefinition.generated.h"

/**
 * 
 */
class UMobaAbility;
UCLASS()
class ABILITY_API UMobaAbilityAssetDefinition : public UAssetDefinitionDefault
{
	GENERATED_BODY()
	
public:
	UMobaAbilityAssetDefinition();

	// UAssetDefinition Begin
	virtual FText GetAssetDisplayName() const override;
	virtual FLinearColor GetAssetColor() const override { return FLinearColor::Red; }
	virtual TSoftClassPtr<UObject> GetAssetClass() const override { return UMobaAbility::StaticClass(); }
	virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;

	virtual bool CanImport() const override { return true; }
	//virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const override;
	//virtual TSharedPtr<class SWidget> GetThumbnailOverlay(const FAssetData& AssetData) const override;
	virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;

private:
	//EAssetTypeCategories::Type MyAssetCategory;

};
