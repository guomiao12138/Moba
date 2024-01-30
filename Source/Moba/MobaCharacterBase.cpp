// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaCharacterBase.h"
#include "GameFrameWork/CharacterMovementComponent.h"

// Sets default values
AMobaCharacterBase::AMobaCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMobaCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMobaCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//auto aa = GetMesh()->ge();
	//float value = aa.Yaw + DeltaTime * 10;
	////SetActorRelativeRotation(FRotator(0, value, 0));
	//GetMesh()->SetWorldRotation(FRotator(0, value, 0));
}

// Called to bind functionality to input
void AMobaCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//CharacterMovement->MoveUpdatedComponent();
}

