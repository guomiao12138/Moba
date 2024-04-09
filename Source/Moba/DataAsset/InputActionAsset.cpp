// Fill out your copyright notice in the Description page of Project Settings.


#include "InputActionAsset.h"
#include "UObject/ObjectSaveContext.h"
#include "GameFramework/PlayerInput.h"

//void UInputActionAsset::Serialize(FArchive& Ar)
//{
//	Super::Serialize(Ar);
//	FString ConfigPath = FPaths::ProjectConfigDir() + ConfigName;
//
//	TArray<FString> value;
//	GConfig->GetArray(TEXT("InputSetting.Action"), TEXT("ActionMappings"), value, ConfigPath);
//	ActionMappings.Empty();
//
//	for (auto v : value)
//	{
//		//EKeys::GetMenuCategoryDisplayName();
//		FInputActionMapping Action;
//		FKey BaseKey(FName("J"));
//		Action.BaseKey = BaseKey;
//		ActionMappings.Add(Action);
//	}
//}

void UInputActionAsset::PostLoad()
{
	Super::PostLoad();

	FString configPath = FPaths::ProjectConfigDir() + ConfigName;

	TArray<FString> value;
	GConfig->GetArray(TEXT("InputSetting.Action"), TEXT("ActionMappings"), value, configPath);
	ActionMappings.Empty();



	TArray<int> flag;

	for (auto v : value)
	{
		for (int i = 0; i < v.Len(); i++)
		{

		}
		FInputActionMapping Action;
		FKey BaseKey(FName("J"));
		Action.BaseKey = BaseKey;
		ActionMappings.Add(Action);
	}
}

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
	if (ConfigName.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("ConfigName Is None, "));
		return;
	}

	if (!ConfigName.EndsWith(TEXT(".ini")))
	{
		UE_LOG(LogTemp, Warning, TEXT("ConfigName should be xxx.ini"));
		return;
	}

	FString configPath = FPaths::ProjectConfigDir() + ConfigName;

	TArray<FString> value;
	for (FInputActionMapping ac : ActionMappings)
	{
		value.Add(FString::Printf(TEXT("(ActionName = %s), (BaseKey = %s), (ModifyKey = %s)"), *ac.ActionName.ToString(), *ac.BaseKey.ToString(), *ac.ModifyKey.ToString()));
	}
	GConfig->SetArray(TEXT("InputSetting.Action"), TEXT("ActionMappings"), value, configPath);

	//for (FInputActionMapping ac : AxisMappings)
	//{
	//	value += FString::Printf(TEXT("(BaseKey = %s), (ModifyKey = %s)"), *ac.BaseKey.ToString(), *ac.ModifyKey.ToString()) + TEXT("\n");
	//}
	//GConfig->SetString(TEXT("InputSetting.Axis"), TEXT("ActionMappings"), *value, ConfigPath);
	GConfig->Flush(false, configPath);
}

TArray<int> UInputActionAsset::FindKeyIndex(FString source, FString flag)
{
	return TArray<int>();
}