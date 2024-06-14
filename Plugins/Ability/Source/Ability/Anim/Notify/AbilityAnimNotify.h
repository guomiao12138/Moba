// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AbilityAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class ABILITY_API UAbilityAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FName Name;
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	DECLARE_MULTICAST_DELEGATE_OneParam(FNotify, FString);

	FNotify NotifyDelegate;
};
