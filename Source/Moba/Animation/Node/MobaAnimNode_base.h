// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNode_AssetPlayerBase.h"
#include "Animation/AnimNode_SequencePlayer.h"
#include "MobaAnimNode_base.generated.h"

/**
 * 
 */
USTRUCT()
struct MOBA_API FMobaAnimNode_base : public FAnimNode_SequencePlayer
{
	GENERATED_BODY()
public:
	FName SlotName;

	void UpdateAsset(UAnimSequenceBase* Asset);

	//FAnimNode_Base
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	//virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;
	//virtual void UpdateAssetPlayer(const FAnimationUpdateContext& Context) override;
	//virtual void Evaluate_AnyThread(FPoseContext& Output) override;
	//virtual void GatherDebugData(FNodeDebugData& DebugData) override;
	//FAnimNode_Base
};
