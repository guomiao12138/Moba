// Fill out your copyright notice in the Description page of Project Settings.


#include "Server.h"

#include "SocketSubsystem.h"
#include "Sockets.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Moba/Setting/SocketDeveloperSettings.h"
#include "Engine/NetDriver.h"
#include "HAL/ConsoleManager.h"
#include "Misc/DefaultValueHelper.h"
#include "Moba/Protobuf/test.pb.h"
#include "TimerManager.h"

UServer::UServer()
{

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

	//GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	CloseAllConnect();
}

void UServer::Init()
{
	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("SendMessage"),
		TEXT("UServer Call SendMessage Test"),
		FConsoleCommandWithArgsDelegate::CreateUObject(this, &UServer::SendMessage),
		ECVF_Default);

	if (CreateSocket())
	{
		USocketDeveloperSettings* Setting = GetMutableDefault<USocketDeveloperSettings>();
		if (Bind(Setting->ip, Setting->port))
		{
			if (Listen())
			{
				ServeRunnable = MakeShareable(new FServerRunnable(TWeakObjectPtr<UServer>(this)));
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
			TSharedRef<FServerConnectRunnable> Runable = MakeShared<FServerConnectRunnable>(RunnableNum, TSharedPtr<FSocket>(ClientSocket));
			test aa;
			aa.set_id(333);
			aa.set_greeting("Proto Test Message");
			std::string sss;
			aa.SerializeToString(&sss);
			//FString temp = FString(sss.c_str());
			TCHAR* SerializeData = FString(sss.c_str()).GetCharArray().GetData();
			int32 size = FCString::Strlen(SerializeData);
			int sent;
			Runable->SendMsg((uint8*)TCHAR_TO_UTF8(SerializeData), size, sent);
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
		return Socket->WaitForPendingConnection(InHasConnect, FTimespan::FromSeconds(0.25f));
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

			FString tryToString(reinterpret_cast<const char*>(Buffer.GetData()));
			int32 sent = 0;
			SendMsg(0, Buffer);
			//if (ClientMap[0]->ClientSocket->Send((uint8*)TCHAR_TO_UTF8(arg.GetCharArray().GetData()), Buffer.Num(), sent))
			//{
			//	UE_LOG(LogTemp, Display, TEXT("Server : SendMessage %s"), *arg);
			//}
		}
	}
}

FServerConnectRunnable::FServerConnectRunnable(int32 InRunnableIndex, TSharedPtr<FSocket> InClientSocket)
{
	RunnableIndex = InRunnableIndex;
	ClientSocket = InClientSocket;
	Thread = FRunnableThread::Create(this, TEXT("Server Connect Thread"));
}

void FServerConnectRunnable::SendMsg(TArray<uint8> InBuffer)
{
	int32 BytesSent = 0;
	ClientSocket->Send(InBuffer.GetData(), InBuffer.Num(), BytesSent);
}

void FServerConnectRunnable::SendMsg(const uint8* Data, int32 Count, int32& BytesSent)
{
	ClientSocket->Send(Data, Count, BytesSent);
}

bool FServerConnectRunnable::IsConnect()
{
	if (ClientSocket->GetConnectionState() == ESocketConnectionState::SCS_Connected)
	{
		return true;
	}
	return false;
}

bool FServerConnectRunnable::Init()
{
	return IsRuning;
}

uint32 FServerConnectRunnable::Run()
{
	while (IsRuning)
	{
		//uint8 content;
		uint32 Datasize = 0;
		int32 BytesRead = 0;

		if (!IsConnect())
		{

		}

		if (ClientSocket->HasPendingData(Datasize))
		{
			TArray<uint8> Buffer;
			Buffer.AddUninitialized(Datasize);

			if (ClientSocket->Recv(Buffer.GetData(), Datasize, BytesRead))
			{
				const std::string cstr(reinterpret_cast<const char*>(Buffer.GetData()), Datasize);
				FString frameAsFString = cstr.c_str();
				UE_LOG(LogTemp, Warning, TEXT("Server RunnableIndex %d Recv Data %s"), RunnableIndex, *frameAsFString);
			}
		}
	}

	return uint32();
}

void FServerConnectRunnable::Stop()
{
	IsRuning = false;
}

void FServerConnectRunnable::Exit()
{

}

FServerConnectRunnable::~FServerConnectRunnable()
{
	if (Thread != nullptr)
	{
		Thread->Kill();
		delete Thread;
		Thread = nullptr;
	}
}

FServerRunnable::FServerRunnable(TWeakObjectPtr<UServer> InOwner)
{
	Server = InOwner;
	Thread = FRunnableThread::Create(this, TEXT("Server Thread"));
}

bool FServerRunnable::Init()
{
	return Server.IsValid();
}

uint32 FServerRunnable::Run()
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

void FServerRunnable::Stop()
{
	IsRuning = false;
}

void FServerRunnable::Exit()
{
}

FServerRunnable::~FServerRunnable()
{
	if (Thread != nullptr)
	{
		Thread->Kill();
		delete Thread;
		Thread = nullptr;
	}
}
