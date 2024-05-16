// Fill out your copyright notice in the Description page of Project Settings.


#include "Client.h"
//#include <Winsock2.h>


#include "SocketSubsystem.h"
#include "Sockets.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Moba/Setting/SocketDeveloperSettings.h"
#include "Engine/NetDriver.h"
#include "Interfaces/IPv4/IPv4Address.h"

UClient::UClient()
{
}

UClient::~UClient()
{
	if (MobaSocketRunnable.IsValid())
	{
		MobaSocketRunnable.Reset();
	}
}

void UClient::Init()
{
	MobaSocketRunnable = MakeShared<FClientSocketRunnable>(TWeakObjectPtr<UClient>(this));
}

void UClient::CreateSocket()
{
	USocketDeveloperSettings* setting = GetMutableDefault<USocketDeveloperSettings>();




}

void UClient::SendMsg(const TArray<uint8>& InBuffer)
{
	MobaSocketRunnable->SendMsg(InBuffer);
}

FClientSocketRunnable::FClientSocketRunnable(TWeakObjectPtr<UClient> InClient)
{
	Client = InClient;
	Thread = FRunnableThread::Create(this, TEXT("ClientSocket Thread"));
}

bool FClientSocketRunnable::Init()
{
	USocketDeveloperSettings* Setting = GetMutableDefault<USocketDeveloperSettings>();
	ServerAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	FIPv4Address IP;
	FIPv4Address::Parse(Setting->ip, IP);
	ServerAddr->SetIp(IP.Value);
	ServerAddr->SetPort(Setting->port);

	Socket = TSharedPtr<FSocket>(ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("ClientSocketRunnable")));

	TSharedRef<FInternetAddr> HostAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool bCanBindAll;
	HostAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(*GLog, bCanBindAll);
	uint32 addr;
	HostAddr->GetIp(addr);
	UE_LOG(LogTemp, Warning, TEXT("Client HostAddr : %s"), *HostAddr->ToString(true));
	return Socket != nullptr;
}

uint32 FClientSocketRunnable::Run()
{
	while (IsRuning)
	{
		if (Socket == nullptr)
		{
			if (!Init())
			{
				UE_LOG(LogTemp, Error, TEXT("Client create socket faild"));
			}
		}
		Tick();
		if (Socket->GetConnectionState() == ESocketConnectionState::SCS_Connected)
		{
			uint32 Datasize = 0;
			int32 BytesRead = 0;

			if (Socket->HasPendingData(Datasize))
			{
				TArray<uint8> Buffer;
				Buffer.AddUninitialized(Datasize);

				if (Socket->Recv(Buffer.GetData(), Datasize, BytesRead))
				{
					const std::string cstr(reinterpret_cast<const char*>(Buffer.GetData()), Datasize);
					FString frameAsFString = cstr.c_str();
					UE_LOG(LogTemp, Warning, TEXT("Client Recv Data %s"), *frameAsFString);
				}
			}
		}
	}


	return uint32();
}

void FClientSocketRunnable::Stop()
{
	IsRuning = false;
}

void FClientSocketRunnable::Exit()
{

}

void FClientSocketRunnable::SendMsg(TArray<uint8> InBuffer)
{
	int32 BytesSent = 0;
	Socket->Send(InBuffer.GetData(), InBuffer.Num(), BytesSent);
}

void FClientSocketRunnable::WaitConnect(float time)
{
	//if (CurrentTime >= time)
	{
		if (Socket->Connect(*ServerAddr))
		{
			FString serialized = TEXT("Client say hello");
			TCHAR* serializedChar = serialized.GetCharArray().GetData();
			int32 size = FCString::Strlen(serializedChar);
			int32 sent = 0;
			if (Socket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent))
			{
				UE_LOG(LogTemp, Warning, TEXT("%s"), *serialized);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Client socket connect faild"));
		}
	}
}

void FClientSocketRunnable::Tick()
{
	CurrentTime = FDateTime::UtcNow();

	if (Socket->GetConnectionState() != ESocketConnectionState::SCS_Connected)
	{
		WaitConnect(0);
	}
}

FClientSocketRunnable::~FClientSocketRunnable()
{
	if (Thread != nullptr)
	{
		Thread->Kill();
		delete Thread;
		Thread = nullptr;
	}
}