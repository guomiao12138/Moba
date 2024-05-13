// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaSocketSubsystem.h"
#include "SocketSubsystem.h"
#include "Sockets.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Moba/Setting/SocketDeveloperSettings.h"
#include "Engine/NetDriver.h"
#include "Server.h"

class UServer;


void UMobaSocketSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Server = NewObject<UServer>(this);
	Server->Init();
}

void UMobaSocketSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

