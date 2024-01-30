// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MobaDatatable.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct FCharacterResource : public FTableRowBase
{
	GENERATED_BODY()



};

class MOBA_API MobaDatatable
{
public:
	MobaDatatable();
	~MobaDatatable();
};
