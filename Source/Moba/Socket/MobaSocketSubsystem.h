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
class UServer;
UCLASS()
class MOBA_API UMobaSocketSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
    UPROPERTY()
	UServer* Server;



public://���صĺ�����������һЩ��ʼ�����ͷŲ���
    virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return true; }
    virtual void Initialize(FSubsystemCollectionBase& Collection)override;
    virtual void Deinitialize()override;

public:
};