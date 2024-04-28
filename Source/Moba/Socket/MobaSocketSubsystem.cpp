// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaSocketSubsystem.h"
#include "SocketSubsystem.h"
#include "Sockets.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Moba/Setting/SocketDeveloperSettings.h"

void UMobaSocketSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	CreateSocket();

}

void UMobaSocketSubsystem::Deinitialize()
{
	Super::Deinitialize();
	if (Socket)
	{
		//Socket->Close();	
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
	}
}

void UMobaSocketSubsystem::CreateSocket()
{
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("MobaSocketSubsystem"), false);
	USocketDeveloperSettings* setting = GetMutableDefault<USocketDeveloperSettings>();

	FString address = setting->ip;
	int32 port = setting->port;
	FIPv4Address ip;
	FIPv4Address::Parse(address, ip);



	TSharedRef addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);


	bool connected = Socket->Connect(*addr);

	if (connected)
	{
		UE_LOG(LogTemp, Display, TEXT("connected"));
	}
	FString serialized = TEXT("loadPlayer|1");
	TCHAR* serializedChar = serialized.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar);
	int32 sent = 0;

	bool successful = Socket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);

	if (successful)
	{
		UE_LOG(LogTemp, Display, TEXT("successful"));
	}

}
