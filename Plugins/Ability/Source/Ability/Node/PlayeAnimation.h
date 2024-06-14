// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityNode.h"
#include "UObject/ObjectMacros.h"
#include "Animation/AnimInstance.h"
#include "PlayeAnimation.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnimationPlayDelegate, FName, NotifyName);
class UAbilityAnimNotify;
UCLASS()
class UPlayeAnimation : public UAbilityNode
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "AnimSequence")
	TObjectPtr<class UAnimSequenceBase> Asset;

	virtual void OnActiveNode() override;
	virtual bool OnDeActiveNode() override;

	virtual void PostLoad() override;

	bool IsNotifyValid(FName NotifyName);

	UFUNCTION()
	void Notify(FString NotifyName);

	FOnMontageBlendingOutStarted BlendingOutDelegate;
	FOnMontageEnded MontageEndedDelegate;
#if WITH_EDITOR
	virtual void AllocateDefaultPins() override;
	virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;
#endif
};
