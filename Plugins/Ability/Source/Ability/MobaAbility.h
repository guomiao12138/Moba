// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MobaAbility.generated.h"

/**
 * 
 */
UCLASS()
class ABILITY_API UMobaAbility : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FName name;


	
};
