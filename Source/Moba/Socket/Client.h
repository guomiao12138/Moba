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

    UFUNCTION(BlueprintCallable)
    void CreateSocket();

public:
	FGuid Guid;
	TSharedPtr<FSocket> Socket;
	
	TSharedPtr<FClientSocketRunnable> MobaSocketRunnable;
};

struct FLocalReceivedPacket;

class FClientSocketRunnable : public FRunnable
{
public:

	TSharedPtr<FSocket> Socket;
	FRunnableThread* Thread = nullptr;
	TAtomic<bool> IsRuning = true;

	TSharedPtr<FSocket> ClientSocket;

public:

	FClientSocketRunnable(TSharedPtr<FSocket>& InSocket);

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
	virtual ~FClientSocketRunnable();

	bool DispatchPacket(FLocalReceivedPacket&& IncomingPacket, int32 NbBytesRead);

};