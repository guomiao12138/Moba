// Fill out your copyright notice in the Description page of Project Settings.


#include "Client.h"
//#include <Winsock2.h>


#include "SocketSubsystem.h"
#include "Sockets.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Moba/Setting/SocketDeveloperSettings.h"
#include "Engine/NetDriver.h"


UClient::UClient()
{
	//CreateSocket();

	//if (Socket.IsValid())
	//{
	//	MobaSocketRunnable = MakeShared<FClientSocketRunnable>(Socket);
	//}
	//Guid = FGuid::NewGuid();
}

UClient::~UClient()
{
	if (Socket.IsValid())
	{
		//Socket->Close();	
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket.Get());
		Socket.Reset();
	}

	if (MobaSocketRunnable.IsValid())
	{
		MobaSocketRunnable.Reset();
	}

	//if (auto driver = GetWorld()->GetNetDriver())
	//{
	//	auto ClientConnections = driver->ClientConnections;
	//	for (auto c : ClientConnections)
	//	{
	//		c->CleanUp();
	//	}
	//}
}

void UClient::CreateSocket()
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

FClientSocketRunnable::FClientSocketRunnable(TSharedPtr<FSocket>& InSocket)
{
	Socket = InSocket;
	Thread = FRunnableThread::Create(this, TEXT("Bridge Background Service Thread"));

	//server
	//ClientSocket->Bind(*addr);
	//ClientSocket->Listen(0);
	bool canbindall;
	TSharedPtr<FInternetAddr> ListenAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(*GLog, canbindall);
	//ListenAddr->SetPort(Port);

	// create a server TCP socket
	ClientSocket = TSharedPtr<FSocket>(ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("MobaSocketSubsystem-listen"), ListenAddr->GetProtocolType()));

	if (!ClientSocket)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not create listen ClientSocket."));
	}
	else
	{
		Socket->SetReuseAddr();
		Socket->SetNoDelay();

		// bind to the address
		if (!Socket->Bind(*ListenAddr))
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to bind listen socket %s in MobaSocketSubsystemServerTCP"), *ListenAddr->ToString(true));
		}
		// listen for connections
		else if (!Socket->Listen(16))
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to listen on socket %s in MobaSocketSubsystemServerTCP"), *ListenAddr->ToString(true));
		}
		else
		{
			// set the port on the listen address to be the same as the port on the socket
			int32 port = Socket->GetPortNo();
			//check((Port == 0 && port != 0) || port == Port);
			ListenAddr->SetPort(port);
		}
	}
}

bool FClientSocketRunnable::Init()
{
	return Socket != nullptr;
}

uint32 FClientSocketRunnable::Run()
{
	while (IsRuning && Socket)
	{
		uint32 size;
		int32 ResultID = 0;
		int32 BytesRead;
		TArray<uint8> content;
		if (Socket->HasPendingData(size))
		{
			content.SetNum(size);
			if (Socket->Recv(content.GetData(), sizeof(int32), BytesRead))
			{
				const std::string cstr(reinterpret_cast<const char*>(content.GetData()), content.Num());
				FString frameAsFString = cstr.c_str();
				UE_LOG(LogTemp, Warning, TEXT("Data %s"), *frameAsFString);
				//FLocalReceivedPacket InCommingpacket;
				//DispatchPacket();
				int32 sent = 0;
				FString serialized = TEXT("aaaaaa");
				TCHAR* serializedChar = serialized.GetCharArray().GetData();
				Socket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), serialized.Len(), sent);
			}
		}

		if (ClientSocket)
		{
			uint32 size1;
			if (ClientSocket->HasPendingData(size1))
			{
				FString des;
				TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
				ClientSocket->Accept(*addr, *des);
				UE_LOG(LogTemp, Warning, TEXT("Data %s"), *des);
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

FClientSocketRunnable::~FClientSocketRunnable()
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
	if (ClientSocket)
	{
		ClientSocket.Reset();
	}
}

bool FClientSocketRunnable::DispatchPacket(FLocalReceivedPacket&& IncomingPacket, int32 NbBytesRead)
{
	return false;
}
