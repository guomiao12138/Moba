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



private:
	TObjectPtr<AMobaCharacterBase> Hero;

protected:

	FVector2D LastPosition;
	int interval = 5;

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(MoveToDelegate, FVector);
	MoveToDelegate MoveTo;

public:
	UPROPERTY(EditAnywhere)
	TArray<class UMobaAbility*> Abilitys;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AMobaCharacterBase> HeroClass;

	AMobaPlayerController();

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void ClickPosition();

	FVector IsMoveCamera();
	void MoveForward(float value);
	void MoveRight(float value);

	void CreateDefaultHero();

};
