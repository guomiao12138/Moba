// Fill out your copyright notice in the Description page of Project Settings.


#include "InputActionAsset.h"
#include "UObject/ObjectSaveContext.h"
#include "GameFramework/PlayerInput.h"

static FString InputConfig = FPaths::ProjectConfigDir() + TEXT("DefaultMoba.ini");

void UInputActionAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UInputActionAsset, ActionMappings))
	{
		//ActionMappings.Add(PropertyChangedEvent.);
	}
}

void UInputActionAsset::PreSaveRoot(FObjectPreSaveRootContext ObjectSaveContext)
{
	Super::PreSaveRoot(ObjectSaveContext);

	for (struct FInputActionKeyMapping aa : ActionMappings)
	{
		//UE_LOG(LogTemp, Display, TEXT("-AxisConfig = (AxisKeyName = "%s", AxisProperties = (DeadZone = 0.25, Exponent = 1.f, Sensitivity = 1.f))"), aa.ActionName, aa.);
		
	}
	//FMLAdapterInputHelper
	//FString value;
	//GConfig->GetString(TEXT("AAAAAA"), TEXT("ActionMappings"), value, InputConfig);
	GConfig->SetInt(TEXT("AAAAAA"), TEXT("index"), 2, InputConfig);
	////GConfig->SetString(TEXT("AAAAAA"), TEXT("ActionMappings"), , InputConfig);
	//GConfig->Flush(true);
}
