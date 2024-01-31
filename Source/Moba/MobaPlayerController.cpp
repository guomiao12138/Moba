// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaPlayerController.h"
#include "Components/InputComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "MobaCharacterBase.h"

AMobaPlayerController::AMobaPlayerController()
{
	ULocalPlayer* LocPlayer = Cast<ULocalPlayer>(Player);
	if (LocPlayer && LocPlayer->ViewportClient)
	{
		LocPlayer->Origin = FVector2D(0.5, 0.5);
	}
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

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, hit.ImpactPoint);

}

FVector AMobaPlayerController::IsMoveCamera()
{
	float x, y;
	int sizeX, sizeY;
	if (GetMousePosition(x, y))
	{
		GetViewportSize(sizeX, sizeY);


		UE_LOG(LogTemp, Display, TEXT("mouse_x : %f, mouse_y : %f, size_x: %d, size_y : %d"), x, y, sizeX, sizeY);
		if (x + 3 >= sizeX || x - 3 <= 0 || y - 3 <= 0 || y + 3 >= sizeY)
		{
			return FVector(x - 0.5 * sizeX, y - 0.5 * sizeY, 0);
		}
	}

	return FVector();
}

void AMobaPlayerController::MoveForward(float value)
{
	FVector dir = IsMoveCamera();
	if (!dir.IsZero())
	{
		if (auto pawn = GetPawn())
		{
			pawn->AddMovementInput(dir * 1);
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
			pawn->AddMovementInput(dir * 1);
		}
	}
}
