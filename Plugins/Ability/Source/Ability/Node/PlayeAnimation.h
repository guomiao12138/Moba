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

UCLASS()
class UPlayeAnimation : public UAbilityNode
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "AnimSequence")
	TObjectPtr<class UAnimSequenceBase> Asset;

	UPROPERTY(BlueprintAssignable)
	FOnAnimationPlayDelegate OnNotifyBegin;

	UPROPERTY(BlueprintAssignable)
	FOnAnimationPlayDelegate OnNotifyEnd;

	UFUNCTION()
	void OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	virtual void OnActiveNode() override;
	virtual bool OnDeActiveNode() override;
	bool IsNotifyValid(FName NotifyName);

	UFUNCTION()
	void OnNotifyBeginReceived(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);

	UFUNCTION()
	void OnNotifyEndReceived(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);

	FOnMontageBlendingOutStarted BlendingOutDelegate;
	FOnMontageEnded MontageEndedDelegate;
#if WITH_EDITOR
	virtual void AllocateDefaultPins() override;
	virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;
#endif
};
