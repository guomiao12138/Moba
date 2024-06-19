// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAnimNode_base.h"
#include "Moba/Animation/MobaAnimInstance.h"

void FMobaAnimNode_base::UpdateAsset(UAnimSequenceBase* Asset)
{
	Sequence = Asset;
}

void FMobaAnimNode_base::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	Super::Initialize_AnyThread(Context);

	//InitialUpdateFunction.SetFromFunction(UMobaAnimInstance::);
}
