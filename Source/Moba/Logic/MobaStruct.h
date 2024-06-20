// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "MobaStruct.generated.h"

USTRUCT(BlueprintType)
struct FAnimConfig
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FSoftObjectPath AnimAsset;

};
