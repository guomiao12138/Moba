// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaCharacterBase.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/SkeletalMeshComponent.h"

#include "MobaPlayerController.h"
#include "Ability/MobaAbilityComponent.h"
#include "Moba/Animation/MobaAnimInstance.h"

// Sets default values
AMobaCharacterBase::AMobaCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//GetMesh()->SetSkeletalMeshAsset();

	AbilityComponent = CreateDefaultSubobject<UMobaAbilityComponent>(TEXT("AbilityComponent"));
}

void AMobaCharacterBase::InitController(AMobaPlayerController* InController)
{
	MobaPlayerController = InController;
	SpawnDefaultController();
	MobaPlayerController->MoveTo.AddUObject(this, &AMobaCharacterBase::MoveTo);
	MobaPlayerController->ActiveAbility.AddUObject(this, &AMobaCharacterBase::ActiveAbility);
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
	

}

// Called to bind functionality to input
void AMobaCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//CharacterMovement->MoveUpdatedComponent();
}

void AMobaCharacterBase::ActiveAbility()
{
	if (GetMesh())
	{
		if (auto inst = Cast<UMobaAnimInstance>(GetMesh()->AnimScriptInstance))
		{
			inst->SetChangeState(ECharacterType::Skill);
			AbilityComponent->ActiveAbility();
		}
	}
}

void AMobaCharacterBase::MoveTo(FVector InLocation)
{
	FVector dir = InLocation - GetActorLocation();
	SetActorRelativeRotation(FRotator(0, dir.Rotation().Yaw, 0));
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), InLocation);
}

