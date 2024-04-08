// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerInput.h"
#include "MobaPlayerInput.generated.h"

/**
 * 
 */
UCLASS()
class MOBA_API UMobaPlayerInput : public UPlayerInput
{
	GENERATED_BODY()
	
public:
	virtual void PostInitProperties() override;
	UMobaPlayerInput();
};
