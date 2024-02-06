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
	 
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//TObjectPtr<UCapsuleComponent> CapsuleComponent;

	//UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly)
	//TObjectPtr<USpringArmComponent> SpringArmComponent;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//TObjectPtr<UCameraComponent> CameraComponent;

	//UPROPERTY(EditAnywhere)
	//TObjectPtr<UStaticMesh> Mesh;


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
