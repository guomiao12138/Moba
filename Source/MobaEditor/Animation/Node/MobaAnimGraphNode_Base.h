// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimGraphNode_Base.h"
#include "Moba/Animation/Node/MobaAnimNode_base.h"
#include "MobaAnimGraphNode_Base.generated.h"

/**
 * 
 */
UCLASS()
class MOBAEDITOR_API UMobaAnimGraphNode_Base : public UAnimGraphNode_Base
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = Settings)
	FMobaAnimNode_base Node;
};
