// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaSocketSubsystem.h"
//#include <Winsock2.h>


#include "SocketSubsystem.h"
#include "Sockets.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Moba/Setting/SocketDeveloperSettings.h"


void UMobaSocketSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	CreateSocket();

	if (Socket.IsValid())
	{
		MobaSocketRunnable = MakeShared<FMobaSocketRunnable>(Socket);
	}

	//FRunnableThread::Create(MobaSocketRunnable.Get(), TEXT("UMobaSocketSubsystem"));
}

void UMobaSocketSubsystem::Deinitialize()
{
	Super::Deinitialize();
	if (Socket.IsValid())
	{
		//Socket->Close();	
		//ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket.Get());
		Socket.Reset();
	}

	if (MobaSocketRunnable.IsValid())
	{
		MobaSocketRunnable.Reset();
	}
}

void UMobaSocketSubsystem::CreateSocket()
{
	USocketDeveloperSettings* setting = GetMutableDefault<USocketDeveloperSettings>();

	Socket = TSharedPtr<FSocket>(ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("MobaSocketSubsystem")));

	FString address = setting->ip;
	int32 port = setting->port;
	FIPv4Address ip;
	FIPv4Address::Parse(address, ip);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
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

	TArray<TSharedRef<FInternetAddr>> addrs = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalBindAddresses();
	for (auto a : addrs)
	{
		if (a->IsPortValid(setting->port))
		{
			uint32 HostIp = 0;
			a->GetIp(HostIp); // will return in host order
			UE_LOG(LogTemp, Warning, TEXT("addrs : ip %d port %d"), HostIp, a->GetPort());
		}
	}
}

FMobaSocketRunnable::FMobaSocketRunnable(TSharedPtr<FSocket>& InSocket)
{
	Socket = InSocket;
	Thread = FRunnableThread::Create(this, TEXT("Bridge Background Service Thread"));
}

bool FMobaSocketRunnable::Init()
{
	return Socket != nullptr;
}

uint32 FMobaSocketRunnable::Run()
{
	while (IsRuning && Socket)
	{
		uint8 Data[512];
		int32 ResultID = 0;
		int32 BytesRead;
		TArray<uint8> content;
		if (Socket->Recv(content.GetData(), sizeof(int32), BytesRead))
		{
			const std::string cstr(reinterpret_cast<const char*>(content.GetData()), content.Num());
			FString frameAsFString = cstr.c_str();
			UE_LOG(LogTemp, Warning, TEXT("Data %s"), *frameAsFString);
			//FLocalReceivedPacket InCommingpacket;
			//DispatchPacket();
		}
	}

	return uint32();
}

void FMobaSocketRunnable::Stop()
{
	IsRuning = false;
}

void FMobaSocketRunnable::Exit()
{
}

void FMobaSocketRunnable::Tick()
{
}

FMobaSocketRunnable::~FMobaSocketRunnable()
{
	//
	if (Socket.IsValid())
	{
		Socket.Reset();
	}
	if (Thread != nullptr)
	{
		Thread->Kill();
		delete Thread;
		Thread = nullptr;
	}
}

bool FMobaSocketRunnable::DispatchPacket(FLocalReceivedPacket&& IncomingPacket, int32 NbBytesRead)
{
	return false;
}
