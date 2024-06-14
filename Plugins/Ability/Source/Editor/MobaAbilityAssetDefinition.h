// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetDefinitionDefault.h"
#include "Ability/MobaAbility.h"
#include "MobaAbilityAssetDefinition.generated.h"

/**
 * 
 */
class UMobaAbility;
UCLASS()
class ABILITYEDITOR_API UMobaAbilityAssetDefinition : public UAssetDefinitionDefault
{
	GENERATED_BODY()
	
public:
	// UAssetDefinition Begin
	virtual FText GetAssetDisplayName() const override;
	virtual FLinearColor GetAssetColor() const override;
	virtual TSoftClassPtr<UObject> GetAssetClass() const override;
	virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;

	virtual bool CanImport() const override { return true; }
	virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;

private:
	//EAssetTypeCategories::Type MyAssetCategory;

};
