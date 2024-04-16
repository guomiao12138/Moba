// Fill out your copyright notice in the Description page of Project Settings.


#include "InputActionAsset.h"
#include "UObject/ObjectSaveContext.h"
#include "GameFramework/PlayerInput.h"

#include "Misc/DefaultValueHelper.h"




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



	/*TArray<FString> value;
	TArray<FString> value1;
	GConfig->GetArray(TEXT("InputSetting.Action"), TEXT("ActionMappings"), value, configPath);
	GConfig->GetArray(TEXT("InputSetting.Action"), TEXT("AxisMappings"), value1, configPath);
	ActionMappings.Empty();

	int flag = -1;
	int flag1 = -1;
	TArray<FString> KeyName;
	value.Append(value1);
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

		if (KeyName.Num() == 3)
		{
			//UE_LOG(LogTemp, Warning, TEXT("%s KeyName is not enough 3"), *configPath);

			FInputActionMapping Action;
			Action.ActionName = EInputAction::GetValueByName(*KeyName[0]);
			Action.BaseKey = FKey(*KeyName[1]);
			Action.ModifyKey = FKey(*KeyName[2]);
			ActionMappings.Add(Action);
			//return;
		}
		if (KeyName.Num() == 2)
		{
			FInputAxisMapping Axis;
			Axis.ActionName = EInputAction::GetValueByName(*KeyName[0]);
			Axis.Key = FKey(*KeyName[1]);
			float scale = 0.f;
			Axis.Scale = FDefaultValueHelper::ParseFloat((*KeyName[2]), scale);
			AxisMappings.Add(Axis);
		}


	}
	*/

	//TArray<FString> value;
	//GConfig->GetArray(TEXT("InputSetting.Action"), TEXT("ActionMappings"), value, configPath);
	//ActionMappings.Empty();
}

void UInputActionAsset::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
}

#if WITH_EDITORONLY_DATA
void UInputActionAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (!PropertyChangedEvent.Property->HasAnyPropertyFlags(EPropertyFlags::CPF_Config))
	{
		return;
	}

	TryUpdateDefaultConfigFile();
}

void UInputActionAsset::PreSaveRoot(FObjectPreSaveRootContext ObjectSaveContext)
{
	//UE_LOG(LogTemp, Warning, TEXT("GetName   %s"), *EInputAction::GetName());

	Super::PreSaveRoot(ObjectSaveContext);

	FString configPath = FPaths::ProjectConfigDir() + ConfigName;

	//TryUpdateDefaultConfigFile();
	SaveConfig();
	//LoadConfig(UInputActionAsset::StaticClass(), *configPath);

	//if (ConfigName.IsEmpty())
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("ConfigName Is None"));
	//	return;
	//}

	//if (!ConfigName.EndsWith(TEXT(".ini")))
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("ConfigName should be xxx.ini"));
	//	return;
	//}

	//FString configPath = FPaths::ProjectConfigDir() + ConfigName;

	//TArray<FString> value;
	//for (FInputActionMapping ac : ActionMappings)
	//{
	//	value.Add(FString::Printf(TEXT("(ActionName = %s), (BaseKey = %s), (ModifyKey = %s)"), *EInputAction::GetName(ac.ActionName).ToString(), *ac.BaseKey.ToString(), *ac.ModifyKey.ToString()));
	//}
	//GConfig->SetArray(TEXT("InputSetting.Action"), TEXT("ActionMappings"), value, configPath);

	//value.Empty();
	//for (FInputAxisMapping ax : AxisMappings)
	//{
	//	value.Add(FString::Printf(TEXT("(ActionName = %s), (Key = %s), (Scale = %f)"), *EInputAction::GetName(ax.ActionName).ToString(), *ax.Key.ToString(), ax.Scale));
	//}
	//GConfig->SetArray(TEXT("InputSetting.Axis"), TEXT("ActionMappings"), value, configPath);

	//GConfig->Flush(false, configPath);
}

#endif

void UInputActionAsset::LoadSettingFile(bool Default)
{
	if (Default)
	{
		FString configPath = FPaths::ProjectConfigDir() + ConfigName;
		LoadConfig(UInputActionAsset::StaticClass(), *configPath);
	}
	else
	{
		ReloadConfig();
	}
}

