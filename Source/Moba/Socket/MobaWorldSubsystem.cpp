// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaWorldSubsystem.h"
#include "Client.h"

void UClientPlayerSubsystem::SendMsg(TArray<FString>& InArgs)
{
	if (Client)
	{
		for (auto arg : InArgs)
		{
			FTCHARToUTF8 Convert(*arg);
			int BytesLength = Convert.Length(); //length of the utf-8 string in bytes (when non-latin letters are used, it's longer than just the number of characters)
			uint8* messageBytes = static_cast<uint8*>(FMemory::Malloc(BytesLength));
			FMemory::Memcpy(messageBytes, (uint8*)TCHAR_TO_UTF8(arg.GetCharArray().GetData()), BytesLength); //mcmpy is required, since TCHAR_TO_UTF8 returns an object with a very short lifetime

			TArray<uint8> result;
			for (int i = 0; i < BytesLength; i++)
			{
				result.Add(messageBytes[i]);
			}

			Client->SendMsg(result);
			FMemory::Free(messageBytes);
		}
	}
}

void UClientPlayerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Client = NewObject<UClient>();
	Client->Init();
}

void UClientPlayerSubsystem::Deinitialize()
{
}
