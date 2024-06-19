// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionAsset.h"
#include "CharacterAnimConfig.generated.h"

/**
 * 
 */
UCLASS()
class MOBA_API UCharacterAnimConfig : public UDeafultSettingAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FAnimConfig AnimConfig[ECharacterType::Max];
};
