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

//namespace EInputAction
//{
//	FORCEINLINE int GetValue(FString name)
//	{
//		UEnum* enumclass = FindObject<UEnum>(nullptr, TEXT("/Script/Moba.EInputAction"));
//		return enumclass->GetValueByName(*name);
//	}
//
//	FName GetName(EInputAction::Type type)
//	{
//		UEnum* enumclass = FindObject<UEnum>(nullptr, TEXT("/Script/Moba.EInputAction"));
//
//		UE_LOG(LogTemp, Warning, TEXT("enumclass name %s "), enumclass->GetFName());
//		return *enumclass->GetNameStringByValue(type);
//	};
//}

void UInputActionAsset::PostLoad()
{
	Super::PostLoad();

	FString configPath = FPaths::ProjectConfigDir() + ConfigName;

	TArray<FString> value;
	GConfig->GetArray(TEXT("InputSetting.Action"), TEXT("ActionMappings"), value, configPath);
	ActionMappings.Empty();



	int flag = -1;
	int flag1 = -1;
	TArray<FString> KeyName;

	for (auto v : value)
	{
		KeyName.Empty();
		for (int i = 0; i < v.Len(); i++)
		{
			if (v[i] == '=')
			{
				flag = i + 2;
			}
			if (v[i] == ')')
			{
				flag1 = i;
			}

			if (flag != -1 && flag1 != -1)
			{
				KeyName.Add(v.Mid(flag, flag1 - flag));
				flag = -1;
				flag1 = -1;
			}
		}

		if (KeyName.Num() < 3)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s KeyName is not enough 3"), *configPath);
			return;
		}

		FInputActionMapping Action;
		Action.ActionName = (EInputAction::Type)EInputAction::GetValue(*KeyName[0]);
		Action.BaseKey = FKey(*KeyName[1]);
		Action.ModifyKey = FKey(*KeyName[2]);
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
		value.Add(FString::Printf(TEXT("(ActionName = %s), (BaseKey = %s), (ModifyKey = %s)"), *EInputAction::GetName(ac.ActionName).ToString(), *ac.BaseKey.ToString(), *ac.ModifyKey.ToString()));
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