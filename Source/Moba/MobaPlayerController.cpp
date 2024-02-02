// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaPlayerController.h"
#include "Components/InputComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "MobaCharacterBase.h"
#include "Slate/SGameLayerManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

AMobaPlayerController::AMobaPlayerController()
{
	CreateDefaultHero();
}

void AMobaPlayerController::BeginPlay()
{
	Super::BeginPlay();


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


	ADDACTION(TEXT("RightClick"), TEXT("ClickPosition"));
	//ADDAXIS(TEXT("MoveForward"), MoveForward);
	//ADDAXIS(TEXT("MoveRight"), MoveRight);

	InputComponent->BindAxis(TEXT("MoveForward"), this, &AMobaPlayerController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &AMobaPlayerController::MoveRight);
}

void AMobaPlayerController::ClickPosition()
{
	FVector2D screenlocation;
	GetMousePosition(screenlocation.X, screenlocation.Y);
	FHitResult hit;
	GetHitResultAtScreenPosition(screenlocation, ECollisionChannel::ECC_WorldStatic, true, hit);

	DrawDebugPoint(GetWorld(), hit.ImpactPoint, 20.f, FColor::Blue, false, 10);

	if (auto player = Cast<AMobaCharacterBase>(GetPawn()))
	{
		FVector vec = hit.ImpactPoint - player->GetActorLocation();
		DrawDebugDirectionalArrow(GetWorld(), player->GetActorLocation(), hit.ImpactPoint, 20.f, FColor::Blue, false, 10.f);
		auto rot = vec.Rotation();
		//player->SetActorRotation(FRotator(0, rot.Yaw, 0));
		player->GetMesh()->SetRelativeRotation(FRotator(0, rot.Yaw, 0));
	}

	MoveTo.Broadcast(hit.ImpactPoint);
}

FVector AMobaPlayerController::IsMoveCamera()
{
	FVector2D mousePosition;
	int sizeX, sizeY;
	FVector2D ViewportPosition;
	FVector dir(0, 0, 0);

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

		UE_LOG(LogTemp, Display, TEXT("mouse_x : %f, mouse_y : %f, size_x: %d, size_y : %d"), mousePosition.X, mousePosition.Y, sizeX, sizeY);


		if (mousePosition.X + interval >= sizeX && mousePosition.Y + interval >= sizeY)
		{
			dir.X = 1;
			dir.Y = -1;
		}
		else if (mousePosition.X + interval >= sizeX && mousePosition.Y - interval <= 0)
		{
			dir.X = -1;
			dir.Y = -1;
		}
		else if (mousePosition.X - interval <= 0 && mousePosition.Y + interval >= sizeY)
		{
			dir.X = 1;
			dir.Y = 1;
		}
		else if (mousePosition.X - interval <= 0 && mousePosition.Y - interval <= 0)
		{
			dir.X = -1;
			dir.Y = 1;
		}
		else if (mousePosition.X - interval <= 0 && mousePosition.Y == LastPosition.Y)
		{
			dir.Y = 1;
		}
		else if (mousePosition.X + interval >= sizeX && mousePosition.Y == LastPosition.Y)
		{
			dir.Y = -1;
		}
		else if (mousePosition.Y - interval <= 0 && mousePosition.X == LastPosition.X)
		{
			dir.X = -1;
		}
		else if (mousePosition.Y + interval >= sizeY && mousePosition.X == LastPosition.X)
		{
			dir.X = 1;
		}		


		LastPosition = mousePosition;
	}

	return dir;
}

void AMobaPlayerController::MoveForward(float value)
{
	FVector dir = IsMoveCamera();
	UE_LOG(LogTemp, Display, TEXT("dir : %f , %f"), dir.X, dir.Y);

	if (!dir.IsZero())
	{
		if (auto pawn = GetPawn())
		{
			pawn->AddMovementInput(dir);
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
	TArray<AActor*> startlocation;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), startlocation);

	FActorSpawnParameters spawnInfo;
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	spawnInfo.ObjectFlags |= RF_Transient;

	Hero = GetWorld()->SpawnActor<AMobaCharacterBase>(AMobaCharacterBase::StaticClass(), startlocation[0]->GetActorTransform(), spawnInfo);

	
	Hero->MobaPlayerController = this;
	//Hero->setcontro
}
