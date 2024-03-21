// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityFactory.h"
#include "Ability/Runtime/MobaAbility.h"

UMobaAbilityFactory::UMobaAbilityFactory()
{
    SupportedClass = UMobaAbility::StaticClass();
    bCreateNew = true;
}

UObject* UMobaAbilityFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    return NewObject<UMobaAbility>(InParent, Class, Name, Flags, Context);
}



//bool UMobaAbilityFactory::ShouldShowInNewMenu() const
//{
//    return false;
//}
