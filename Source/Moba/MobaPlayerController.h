// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobaPlayerControllerBase.h"
#include "MobaPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MOBA_API AMobaPlayerController : public AMobaPlayerControllerBase
{
	GENERATED_BODY()

protected:

	FVector2D LastPosition;
	int interval = 5;

public:
	AMobaPlayerController();

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void ClickPosition();

	FVector IsMoveCamera();
	void MoveForward(float value);
	void MoveRight(float value);


};
