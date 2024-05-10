// Fill out your copyright notice in the Description page of Project Settings.


#include "Server.h"

#include "SocketSubsystem.h"
#include "Sockets.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Moba/Setting/SocketDeveloperSettings.h"
#include "Engine/NetDriver.h"
#include "HAL/ConsoleManager.h"

#include "Misc/DefaultValueHelper.h"

#include "TimerManager.h"
UServer::UServer()
{
	FConsoleManager& ConsoleManager = (FConsoleManager&)IConsoleManager::Get();
	ConsoleManager.RegisterConsoleCommand(
		TEXT("SendMessage"),
		TEXT("UServer Call SendMessage Test"),
		FConsoleCommandWithArgsDelegate::CreateUObject(this, &UServer::SendMessage),
		ECVF_Default);
}

UServer::~UServer()
{
	if (ServeRunnable.IsValid())
	{
		ServeRunnable.Reset();
	}

	if (Socket.IsValid())
	{
		Socket->Close();
		Socket.Reset();
	}

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	CloseAllConnect();
}

void UServer::Init()
{
	if (CreateSocket())
	{
		USocketDeveloperSettings* Setting = GetMutableDefault<USocketDeveloperSettings>();
		if (Bind(Setting->ip, Setting->port))
		{
			if (Listen())
			{
				ServeRunnable = MakeShareable(new FServeRunnable(TWeakObjectPtr<UServer>(this)));
				//GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateUObject(this, &UServer::Test), Setting->CheckAccpetRate, true);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Server bind faild"));
	}
}

bool UServer::CreateSocket()
{
	Socket = TSharedPtr<FSocket>(ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("MobaServer")));

	return Socket.IsValid();
}

bool UServer::Bind(FString InIp, int InPort)
{
	bool bBind = false;

	if (Socket.IsValid())
	{
		TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
		FIPv4Address ip;
		FIPv4Address::Parse(InIp, ip);
		Addr->SetIp(ip.Value);
		Addr->SetPort(InPort);
		if (Socket->Bind(*Addr))
		{
			bBind = true;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Server bind faild"));
		}
	}
	return bBind;
}

bool UServer::Listen(int32 InListenNum)
{
	bool bListen = false;

	if (Socket.IsValid())
	{
		if (Socket->Listen(InListenNum))
		{
			bListen = true;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Server listen faild"));
		}
	}

	return bListen;
}

void UServer::Accept()
{
	if (Socket.IsValid())
	{
		TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
		FString des;
		FSocket* ClientSocket = Socket->Accept(*addr, TEXT("Client Connect"));
		if (ClientSocket)
		{
			TSharedRef<FServeConnectRunnable> Runable = MakeShared<FServeConnectRunnable>(RunnableNum, TSharedPtr<FSocket>(ClientSocket));
			ClientMap.Add(RunnableNum, Runable);
			RunnableNum++;
			UE_LOG(LogTemp, Display, TEXT("Client is connected, RunnableIndex : %d"), RunnableNum);
		}
	}
}

void UServer::SendMsg(int32 InRunnableIndex, TArray<uint8> InBuffer)
{
	if (ClientMap.Contains(InRunnableIndex))
	{
		ClientMap[InRunnableIndex]->SendMsg(InBuffer);
	}
}

bool UServer::HasConnection(bool& InHasConnect)
{
	if (Socket.IsValid())
	{
		return Socket->HasPendingConnection(InHasConnect);
	}
	InHasConnect = false;
	return false;
}

void UServer::CloseClientConnect(int InRunnableIndex)
{
	if (ClientMap.Contains(InRunnableIndex))
	{
		ClientMap[InRunnableIndex]->ClientSocket->Close();
		ClientMap[InRunnableIndex].Get().Stop();
		ClientMap.Remove(InRunnableIndex);
	}
}

void UServer::CloseAllConnect()
{
	for (auto ky : ClientMap)
	{
		CloseClientConnect(ky.Key);
	}
}

void UServer::Test()
{
	if (ClientMap.Num() > 0)
	{
		FString serialized = TEXT("TestTestTestTestTestTestTestTest");
		TCHAR* serializedChar = serialized.GetCharArray().GetData();
		int32 size = FCString::Strlen(serializedChar);
		int32 sent = 0;

		ClientMap[0]->ClientSocket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);
	}
}

void UServer::SendMessage(const TArray<FString>& Args)
{
	if (ClientMap.Num() > 0)
	{
		TArray<uint8> Buffer;
		for (auto arg : Args)
		{
			Buffer.Add(*(uint8*)TCHAR_TO_UTF8(arg.GetCharArray().GetData()));
		}
		ClientMap[0]->SendMsg(Buffer);
	}
}

FServeConnectRunnable::FServeConnectRunnable(int32 InRunnableIndex, TSharedPtr<FSocket> InClientSocket)
{
	RunnableIndex = InRunnableIndex;
	ClientSocket = InClientSocket;
	Thread = FRunnableThread::Create(this, TEXT("Server Connect Thread"));
}

void FServeConnectRunnable::SendMsg(TArray<uint8> InBuffer)
{
	int32 BytesSent = 0;
	ClientSocket->Send(InBuffer.GetData(), InBuffer.Num(), BytesSent);
}

bool FServeConnectRunnable::Init()
{
	return IsRuning;
}

uint32 FServeConnectRunnable::Run()
{
	while (IsRuning)
	{
		//uint8 content;
		uint32 Datasize = 0;
		int32 BytesRead = 0;

		if (ClientSocket->HasPendingData(Datasize))
		{
			TArray<uint8> Buffer;
			Buffer.AddUninitialized(Datasize);

			if (ClientSocket->Recv(Buffer.GetData(), Datasize, BytesRead))
			{
				const std::string cstr(reinterpret_cast<const char*>(Buffer.GetData()), Datasize);
				FString frameAsFString = cstr.c_str();
				UE_LOG(LogTemp, Display, TEXT("Client Recv Data %s"), *frameAsFString);
			}
		}
	}

	return uint32();
}

void FServeConnectRunnable::Stop()
{
	IsRuning = false;
}

void FServeConnectRunnable::Exit()
{

}

FServeConnectRunnable::~FServeConnectRunnable()
{
	if (Thread != nullptr)
	{
		Thread->Kill();
		delete Thread;
		Thread = nullptr;
	}
}

FServeRunnable::FServeRunnable(TWeakObjectPtr<UServer> InOwner)
{
	Server = InOwner;
	Thread = FRunnableThread::Create(this, TEXT("Server Thread"));
}

bool FServeRunnable::Init()
{
	return Server.IsValid();
}

uint32 FServeRunnable::Run()
{
	while (IsRuning && Server.IsValid())
	{
		bool HasConnect;
		if (Server.Get()->HasConnection(HasConnect))
		{
			if (HasConnect)
			{
				Server->Accept();
			}
		}
	}
	return uint32();
}

void FServeRunnable::Stop()
{
	IsRuning = false;
}

void FServeRunnable::Exit()
{
}

FServeRunnable::~FServeRunnable()
{
	if (Thread != nullptr)
	{
		Thread->Kill();
		delete Thread;
		Thread = nullptr;
	}
}
