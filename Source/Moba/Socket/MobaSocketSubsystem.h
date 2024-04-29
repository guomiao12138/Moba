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
public:

	FMobaSocketRunnable(TSharedPtr<FSocket>& InSocket);

	virtual bool Init() override;
	/**
	 * Runs the runnable object.
	 *
	 * This is where all per object thread work is done. This is only called if the initialization was successful.
	 *
	 * @return The exit code of the runnable object
	 * @see Init, Stop, Exit
	 */
	virtual uint32 Run() override;

	/**
	 * Stops the runnable object.
	 *
	 * This is called if a thread is requested to terminate early.
	 * @see Init, Run, Exit
	 */
	virtual void Stop() override;

	/**
	 * Exits the runnable object.
	 *
	 * Called in the context of the aggregating thread to perform any cleanup.
	 * @see Init, Run, Stop
	 */
	virtual void Exit() override;

	/**
	 * Gets single thread interface pointer used for ticking this runnable when multi-threading is disabled.
	 * If the interface is not implemented, this runnable will not be ticked when FPlatformProcess::SupportsMultithreading() is false.
	 *
	 * @return Pointer to the single thread interface or nullptr if not implemented.
	 */

	virtual void Tick() override;
	virtual class FSingleThreadRunnable* GetSingleThreadInterface()
	{
		return this;
	}

	virtual ~FMobaSocketRunnable();


	bool DispatchPacket(FLocalReceivedPacket&& IncomingPacket, int32 NbBytesRead);

};