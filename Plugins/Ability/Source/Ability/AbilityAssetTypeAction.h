// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

/**
 * 
 */

class ABILITY_API FAbilityAssetTypeAction : public FAssetTypeActions_Base
{
public:

	FAbilityAssetTypeAction(EAssetTypeCategories::Type Type);

	virtual UClass* GetSupportedClass() const override;
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;


private:
	EAssetTypeCategories::Type MyAssetCategory;
};
