// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaPlayerController.h"
#include "Components/InputComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "MobaCharacterBase.h"

AMobaPlayerController::AMobaPlayerController()
{

}

void AMobaPlayerController::BeginPlay()
{
	Super::BeginPlay();


}

void AMobaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent->AddActionBinding();
	//InputComponent->BindAction(TEXT("Click"), EInputEvent::IE_Pressed, this, &AMobaPlayerController::ClickPosition);


#define ADDACTION(name, function)\
{\
	FInputActionBinding ActionBinding(name, EInputEvent::IE_Pressed); \
	ActionBinding.ActionDelegate.BindDelegate(this, &AMobaPlayerController::ClickPosition); \
	InputComponent->AddActionBinding(ActionBinding);\
}\
	

	ADDACTION(TEXT("RightClick"), TEXT("ClickPosition"));
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
