// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "MobaAbilityFactory.generated.h"

/**
 * 
 */
UCLASS()
class ABILITY_API UMobaAbilityFactory : public UFactory
{
	GENERATED_BODY()
	
public:
	UMobaAbilityFactory();
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn);
	//virtual bool CanCreateNew() const override;
	//virtual bool ShouldShowInNewMenu() const override;
};
