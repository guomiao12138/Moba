// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaPlayerInput.h"
static FString InputConfig = FPaths::ProjectConfigDir() + TEXT("DefaultMoba.ini");
void UMobaPlayerInput::PostInitProperties()
{
	Super::PostInitProperties();

	FString value;
	GConfig->GetString(TEXT("AAAAAA"), TEXT("ActionMappings"), value, InputConfig);
	GConfig->SetInt(TEXT("AAAAAA"), TEXT("index"), 2, InputConfig);
	//GConfig->SetString(TEXT("AAAAAA"), TEXT("ActionMappings"), , InputConfig);
	GConfig->Flush(true);


}

UMobaPlayerInput::UMobaPlayerInput()
{
	
}
