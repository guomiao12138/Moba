// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaCameraPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMobaCameraPawn::AMobaCameraPawn()
{
	
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	if (RootComponent)
	{
		//RootComponent->MoveComponent(FVector::ZeroVector, FRotator::ZeroRotator, true, nullptr, MOVECOMP_NoFlags, ETeleportType::None);
	}
	//Mesh = CreateDefaultSubobject<UStaticMesh>(TEXT("StaticMeshComponent"));
	//SetRootComponent(Mesh);
	//Mesh = CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	//SpringArmComponent->SetupAttachment(Mesh);

	//CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(ACharacter::CapsuleComponentName);
	//CapsuleComponent->InitCapsuleSize(34.0f, 88.0f);
	//SetRootComponent(CapsuleComponent);
	//SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	//SpringArmComponent->TargetArmLength = 1200;
	////SpringArmComponent->SetRelativeRotation(FRotator(0, 0, 0));
	//CameraComponent->SetupAttachment(CapsuleComponent);


	////SpringArmComponent
	//CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	////CameraComponent->AttachToComponent(SpringArmComponent,FAttachmentTransformRules::SnapToTargetIncludingScale);
	//CameraComponent->SetupAttachment(SpringArmComponent);
	SetActorRotation(FRotator(0, 180, 0));
}

// Called when the game starts or when spawned
void AMobaCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	//SetActorRotation(FRotator(0, 180, 0));

}

// Called every frame
void AMobaCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//SetActorRotation(GetActorRotation() + for);
}

// Called to bind functionality to input
void AMobaCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

