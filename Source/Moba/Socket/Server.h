// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Server.generated.h"

/**
 * 
 */
class FServerRunnable;
class FServerConnectRunnable;
UCLASS()
class MOBA_API UServer : public UObject
{
	GENERATED_BODY()
	friend class FServeRunnable;
protected:
	TMap<int32, TSharedRef<FServerConnectRunnable>> ClientMap;

	int32 RunnableNum;

	TSharedPtr<FSocket> Socket;

	FTimerHandle TimerHandle;

public:

	UServer();
	~UServer();

	virtual void Init();
    UFUNCTION(BlueprintCallable)
    bool CreateSocket();
	bool Bind(FString InIp, int InPort);
	bool Listen(int32 InListenNum = 128);
	void Accept();
	void SendMsg(int32 InRunnableIndex, TArray<uint8> InBuffer);
	bool HasConnection(bool& InHasConnect);
	void CloseClientConnect(int InRunnableIndex);
	void CloseAllConnect();

	void Test();
public:
	
	TSharedPtr<FServerRunnable> ServeRunnable;

	UFUNCTION()
	void SendMessage(const TArray<FString>& Args);
};

class FServerConnectRunnable : public FRunnable
{
public:
	int32 RunnableIndex = 0;
	TSharedPtr<FSocket> ClientSocket;
	FRunnableThread* Thread = nullptr;
	TAtomic<bool> IsRuning = true;
	//TSharedPtr<UServer> Server;
public:

	FServerConnectRunnable(int32 InRunnableIndex, TSharedPtr<FSocket> InClientSocket);
	void SendMsg(TArray<uint8> InBuffer);
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
	virtual ~FServerConnectRunnable();
};



class FServerRunnable : public FRunnable
{
public:
	TWeakObjectPtr<UServer> Server;
	FRunnableThread* Thread = nullptr;
	TAtomic<bool> IsRuning = true;
public:
	FServerRunnable(TWeakObjectPtr<UServer> InOwner);
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
	virtual ~FServerRunnable();
};
