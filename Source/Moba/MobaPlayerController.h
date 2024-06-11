// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobaPlayerControllerBase.h"
#include "MobaPlayerController.generated.h"

/**
 * 
 */
class AMobaCharacterBase;

UCLASS()
class MOBA_API AMobaPlayerController : public AMobaPlayerControllerBase
{
	GENERATED_BODY()


	TObjectPtr<AMobaCharacterBase> Hero;


protected:


	FVector2D LastPosition;
	int interval = 5;

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(MoveToDelegate, FVector);
	MoveToDelegate MoveTo;

	DECLARE_MULTICAST_DELEGATE(FActiveAbility);
	FActiveAbility ActiveAbility;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AMobaCharacterBase> HeroClass;

	AMobaPlayerController();

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
	virtual void InitInputSystem() override;


	FVector IsMoveCamera();
	void MoveForward(float value);
	void MoveRight(float value);
	void ClickPosition();
	void Q();
	void W();
	void E();
	void R();

	void CreateDefaultHero();

	UFUNCTION(BlueprintPure)
	AMobaCharacterBase* GetCurrentHero() { return Hero; };

};
