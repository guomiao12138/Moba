// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "AssetDefinitionClasses.h"

/**
 * 
 */

class FAbilityAssetTypeAction : public FAssetTypeActions_Base
{
public:
	FAbilityAssetTypeAction(EAssetTypeCategories::Type Categeory);

	virtual UClass* GetSupportedClass() const override;
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;

protected:
	// FAssetTypeActions_Blueprint
	  //该资产是否可以创建派生蓝图
	//virtual bool CanCreateNewDerivedBlueprint() const override { return false; }
	////返回负责创建此类型Blueprint的工厂
	//virtual UFactory* GetFactoryForBlueprintType(UBlueprint* InBlueprint) const override;


private:
	EAssetTypeCategories::Type MyAssetCategory;
};
