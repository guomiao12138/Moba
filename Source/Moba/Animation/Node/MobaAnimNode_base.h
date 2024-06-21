// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNode_AssetPlayerBase.h"
#include "Animation/AnimNode_SequencePlayer.h"
#include "AnimNodes/AnimNode_BlendSpacePlayer.h"
#include "Moba/Logic/MobaEnum.h"
#include "MobaAnimNode_base.generated.h"

/**
 * 
 */

USTRUCT()
struct FMobaAnimNode_base
{
	GENERATED_BODY()
public:

};

USTRUCT()
struct MOBA_API FMobaAnimNode_Sequence : public FAnimNode_SequencePlayer, public FMobaAnimNode_base
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECharacterType::Type> SlotName = ECharacterType::None;
};

USTRUCT()
struct MOBA_API FMobaAnimNode_BlendSpace : public FAnimNode_BlendSpacePlayer, public FMobaAnimNode_base
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECharacterType::Type> SlotName = ECharacterType::None;
};
