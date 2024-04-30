// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "MobaSocketSubsystem.generated.h"

/**
 * 
 */
class FMobaSocketRunnable;
UCLASS()
class MOBA_API UMobaSocketSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:




public://重载的函数，可以做一些初始化和释放操作
    virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return true; }
    virtual void Initialize(FSubsystemCollectionBase& Collection)override;
    virtual void Deinitialize()override;

    UFUNCTION(BlueprintCallable)
    void CreateSocket();

public:
	TSharedPtr<FSocket> Socket;
	
	TSharedPtr<FMobaSocketRunnable> MobaSocketRunnable;
};

struct FLocalReceivedPacket;

class FMobaSocketRunnable : public FRunnable , public FSingleThreadRunnable
{
public:

	TSharedPtr<FSocket> Socket;
	FRunnableThread* Thread = nullptr;
	TAtomic<bool> IsRuning = true;

	TSharedPtr<FSocket> SeverSocket;

public:

	FMobaSocketRunnable(TSharedPtr<FSocket>& InSocket);

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
	virtual void Tick() override;
	virtual class FSingleThreadRunnable* GetSingleThreadInterface()
	{
		return this;
	}

	virtual ~FMobaSocketRunnable();


	bool DispatchPacket(FLocalReceivedPacket&& IncomingPacket, int32 NbBytesRead);

};