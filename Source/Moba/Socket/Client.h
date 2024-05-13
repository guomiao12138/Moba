// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client.generated.h"

/**
 * 
 */
class FClientSocketRunnable;
UCLASS()
class MOBA_API UClient : public UObject
{
	GENERATED_BODY()

protected:




public:
	UClient();
	~UClient();

	void Init();
    void CreateSocket();
	void SendMsg(const TArray<uint8>& InBuffer);
public:
	FGuid Guid;
	
	TSharedPtr<FClientSocketRunnable> MobaSocketRunnable;
};

class FClientSocketRunnable : public FRunnable , public FSingleThreadRunnable
{
public:

	TWeakObjectPtr<UClient> Client;
	TSharedPtr<FSocket> Socket;
	FRunnableThread* Thread = nullptr;
	TAtomic<bool> IsRuning = true;
	TSharedPtr<FInternetAddr> ServerAddr;
	FDateTime CurrentTime;

public:

	FClientSocketRunnable(TWeakObjectPtr<UClient> InClient);
	virtual ~FClientSocketRunnable();

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

	void SendMsg(TArray<uint8> InBuffer);

	void WaitConnect(float time);

	virtual void Tick() override;
};