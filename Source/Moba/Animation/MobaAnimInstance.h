// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimExecutionContext.h"
#include "MobaAnimInstance.generated.h"

/**
 * 
 */
struct FAnimUpdateContext;
UCLASS()
class MOBA_API UMobaAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void aaa(UPARAM(ref)FAnimUpdateContext& Context, UPARAM(ref)FAnimNodeReference& Node);

};
