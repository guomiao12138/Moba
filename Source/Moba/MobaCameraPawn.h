// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MobaCameraPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class MOBA_API AMobaCameraPawn : public APawn
{
	GENERATED_BODY()


protected:
	 
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	TObjectPtr<UCameraComponent> CameraComponent;


public:
	// Sets default values for this pawn's properties
	AMobaCameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
