// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaCameraPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMobaCameraPawn::AMobaCameraPawn()
{
	//SetActorRotation(FRotator(0, -90, 0));

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
}

// Called when the game starts or when spawned
void AMobaCameraPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMobaCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMobaCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

