// Fill out your copyright notice in the Description page of Project Settings.

#include "MobaPlayerController.h"

#include "Input/MobaPlayerInput.h"

#include "Components/InputComponent.h"
#include "MobaCharacterBase.h"
#include "Slate/SGameLayerManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
//#include "Ability/MobaAbility.h"

#include "SocketSubsystem.h"
#include "Sockets.h"
#include "Interfaces/IPv4/IPv4Address.h"

#include "Subsystems/SubsystemBlueprintLibrary.h"
#include "Socket/MobaSocketSubsystem.h"
AMobaPlayerController::AMobaPlayerController()
{
	OverridePlayerInputClass = UMobaPlayerInput::StaticClass();
}

void AMobaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	FInputModeGameAndUI gameinputmode;
	gameinputmode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(gameinputmode);
	
	CreateDefaultHero();

	if (Hero)
	{
		auto location = Hero->GetActorLocation();
		//UE_LOG(LogTemp, Display, TEXT("mouse_x : %f, mouse_y : %f, size_x: %d, size_y : %d"), location.X, location.Y, location.Z);
	}
}

void AMobaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

#define ADDACTION(name, function)\
{\
	FInputActionBinding ActionBinding(name, EInputEvent::IE_Pressed); \
	ActionBinding.ActionDelegate.BindDelegate(this, function); \
	InputComponent->AddActionBinding(ActionBinding);\
}\
	

#define ADDAXIS(name, function) InputComponent->BindAxis(name, this, &AMobaPlayerController::function);
	//InputComponent->BindAction();

	//ADDACTION(TEXT("RightClick"), TEXT("ClickPosition"));
	//ADDAXIS(TEXT("MoveForward"), MoveForward);
	//ADDAXIS(TEXT("MoveRight"), MoveRight);

	InputComponent->BindAxis(TEXT("MoveForward"), this, &AMobaPlayerController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &AMobaPlayerController::MoveRight);
	InputComponent->BindAction(TEXT("ClickPosition"), EInputEvent::IE_Pressed, this, &AMobaPlayerController::ClickPosition);
}

void AMobaPlayerController::InitInputSystem()
{
	Super::InitInputSystem();

	if (auto input = Cast<UMobaPlayerInput>(PlayerInput))
	{
		input->InitInputSetting();
	}

}

void AMobaPlayerController::ClickPosition()
{



	FVector2D screenlocation;
	GetMousePosition(screenlocation.X, screenlocation.Y);
	FHitResult hit;
	GetHitResultAtScreenPosition(screenlocation, ECollisionChannel::ECC_Camera, true, hit);

	DrawDebugPoint(GetWorld(), hit.ImpactPoint, 20.f, FColor::Blue, false, 10);

	//FActorSpawnParameters Params;
	//Params.Owner = this;
	//Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//if (auto aa = GetWorld()->SpawnActor<UMobaAbility>(hit.ImpactPoint, FRotator::ZeroRotator, Params))
	//{
	//	UE_LOG(LogTemp, Display, TEXT("SpawnActor"));
	//} 


	if (auto player = Cast<AMobaCharacterBase>(GetPawn()))
	{
		FVector vec = hit.ImpactPoint - player->GetActorLocation();
		DrawDebugDirectionalArrow(GetWorld(), player->GetActorLocation(), hit.ImpactPoint, 20.f, FColor::Blue, false, 10.f);
		auto rot = vec.Rotation();
		//player->SetActorRotation(FRotator(0, rot.Yaw, 0));
		//player->GetMesh()->SetRelativeRotation(FRotator(0, rot.Yaw, 0));
	}

	MoveTo.Broadcast(hit.Location);
}

FVector AMobaPlayerController::IsMoveCamera()
{
	FVector2D mousePosition;
	int sizeX, sizeY;
	FVector dir(0, 0, 0);
	FVector2D ViewportPosition;
	static int dirstep = 1;
	static int forwardstep = -dirstep;
	static int backstep = dirstep;
	static int rightstep = -dirstep;
	static int leftstep = dirstep;
	
	if (GetMousePosition(mousePosition.X, mousePosition.Y))
	{
		GetViewportSize(sizeX, sizeY);

		ULocalPlayer* LocPlayer = Cast<ULocalPlayer>(Player);
		if (LocPlayer && LocPlayer->ViewportClient)
		{
			TSharedPtr<IGameLayerManager> GameLayerManager = LocPlayer->ViewportClient->GetGameLayerManager();
			if (GameLayerManager.IsValid())
			{
				const FGeometry& ViewportGeometry = GameLayerManager->GetViewportWidgetHostGeometry();
				ViewportPosition = ViewportGeometry.GetLocalPositionAtCoordinates(FVector2D(0.5, 0.5));
			}
		}


		//dir.X = mousePosition.X <= ViewportPosition.X ? -1 : 1;
		//dir.Y = mousePosition.Y <= ViewportPosition.Y ? 1 : -1;

		//UE_LOG(LogTemp, Display, TEXT("mouse_x : %f, mouse_y : %f, size_x: %d, size_y : %d"), mousePosition.X, mousePosition.Y, sizeX, sizeY);


		if (mousePosition.X + interval >= sizeX && mousePosition.Y + interval >= sizeY)
		{
			dir.X = rightstep;
			dir.Y = backstep;
		}
		else if (mousePosition.X + interval >= sizeX && mousePosition.Y - interval <= 0)
		{
			dir.X = rightstep;
			dir.Y = forwardstep;
		}
		else if (mousePosition.X - interval <= 0 && mousePosition.Y + interval >= sizeY)
		{
			dir.X = leftstep;
			dir.Y = backstep;
		}
		else if (mousePosition.X - interval <= 0 && mousePosition.Y - interval <= 0)
		{
			dir.X = leftstep;
			dir.Y = forwardstep;
		}
		else if (mousePosition.X - interval <= 0 && mousePosition.Y == LastPosition.Y)
		{
			dir.Y = leftstep;
		}
		else if (mousePosition.X + interval >= sizeX && mousePosition.Y == LastPosition.Y)
		{
			dir.Y = rightstep;
		}
		else if (mousePosition.Y - interval <= 0 && mousePosition.X == LastPosition.X)
		{
			dir.X = forwardstep;
		}
		else if (mousePosition.Y + interval >= sizeY && mousePosition.X == LastPosition.X)
		{
			dir.X = backstep;
		}		


		LastPosition = mousePosition;
	}

	return dir;
}

void AMobaPlayerController::MoveForward(float value)
{
	FVector dir = IsMoveCamera();
	if (!dir.IsZero())
	{
		if (auto pawn = GetPawn())
		{
			pawn->AddMovementInput(dir);
			//UE_LOG(LogTemp, Display, TEXT("dir : %f , %， %f"), dir.X, dir.Y, dir.Z);
		}
	}
}

void AMobaPlayerController::MoveRight(float value)
{
	FVector dir = IsMoveCamera();
	if (!dir.IsZero())
	{
		if (auto pawn = GetPawn())
		{
			pawn->AddMovementInput(dir);
		}
	}
}

void AMobaPlayerController::CreateDefaultHero()
{
	FActorSpawnParameters spawnInfo;
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	spawnInfo.ObjectFlags |= RF_Transient;
	GetPawn()->SetActorRotation(FRotator(0, 180, 0));
	Hero = GetWorld()->SpawnActor<AMobaCharacterBase>(HeroClass, GetPawn()->GetActorTransform(), spawnInfo);
	if(Hero)
	{
		Hero->InitController(this);
	}
}
