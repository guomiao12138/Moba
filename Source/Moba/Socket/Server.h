// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Server.generated.h"

/**
 * 
 */
class FServeRunnable;
class FServeConnectRunnable;
UCLASS()
class MOBA_API UServer : public UObject
{
	GENERATED_BODY()
	friend class FServeRunnable;
protected:
	TMap<int32, TSharedRef<FServeConnectRunnable>> ClientMap;

	int32 RunnableNum;

	TSharedPtr<FSocket> Socket;

	FTimerHandle TimerHandle;

public://重载的函数，可以做一些初始化和释放操作

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
	
	TSharedPtr<FServeRunnable> ServeRunnable;

	UFUNCTION()
	void SendMessage(const TArray<FString>& Args);
};

class FServeConnectRunnable : public FRunnable
{
public:
	int32 RunnableIndex = 0;
	TSharedPtr<FSocket> ClientSocket;
	FRunnableThread* Thread = nullptr;
	TAtomic<bool> IsRuning = true;
	//TSharedPtr<UServer> Server;
public:

	FServeConnectRunnable(int32 InRunnableIndex, TSharedPtr<FSocket> InClientSocket);
	void SendMsg(TArray<uint8> InBuffer);
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
	virtual ~FServeConnectRunnable();
};



class FServeRunnable : public FRunnable
{
public:
	TWeakObjectPtr<UServer> Server;
	FRunnableThread* Thread = nullptr;
	TAtomic<bool> IsRuning = true;
public:
	FServeRunnable(TWeakObjectPtr<UServer> InOwner);
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
	virtual ~FServeRunnable();
};
