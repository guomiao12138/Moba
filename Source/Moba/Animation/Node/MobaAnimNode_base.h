// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNode_AssetPlayerBase.h"
#include "MobaAnimNode_base.generated.h"

/**
 * 
 */
USTRUCT(BlueprintInternalUseOnly)
struct FMobaAnimNode_base : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	FPoseLink Base;
};
