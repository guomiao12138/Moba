// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaCharacterBase.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "PhysicsEngine/PhysicsAsset.h"

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

	GetMesh()->SetSimulatePhysics(true);
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
	
	UpdateBoneIndex();
}

// Called every frame
void AMobaCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UpdatePlayFootHit();
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

void AMobaCharacterBase::UpdateBoneIndex()
{
	if (GetMesh())
	{
		RightBone = GetMesh()->GetPhysicsAsset()->FindBodyIndex(TEXT("foot_r"));
		LeftBone = GetMesh()->GetPhysicsAsset()->FindBodyIndex(TEXT("foot_l"));
		//GetMesh()->Bodies[RightBone]->bSimulatePhysics = true;
		//GetMesh()->Bodies[LeftBone]->bSimulatePhysics = true;
	}
}

void AMobaCharacterBase::UpdatePlayFootHit()
{
	if (GetMesh())
	{
		FHitResult OutLeftHit;
		FVector Location;
		if (RightBone != INDEX_NONE)
		{
			//OutLeftTansfrom = GetMesh()->GetRefPosePosition(LeftBone);
			Location = GetMesh()->GetBoneLocation(TEXT("foot_r"));
			//UE_LOG(LogTemp, Warning, TEXT("OutLeftTansfrom : %s"), *OutLeftTansfrom.GetLocation().ToString());
			FVector End = FVector(0, 0, -1) * 1000 + Location;
			//Fcollsio
			bool LeftHit = GetWorld()->LineTraceSingleByChannel(OutLeftHit, Location, End, ECollisionChannel::ECC_GameTraceChannel3);
			//bool LeftHit = GetMesh()->Bodies[RightBone]->LineTrace(OutLeftHit, Location, End, true, true);
			DrawDebugLine(GetWorld(), Location, End, FColor::Black, false, -1, 0, 10);
			if (LeftHit)
			{
				UE_LOG(LogTemp, Warning, TEXT("OutLeftTansfrom : %d"), OutLeftHit.Distance);
			}
		}
		//FHitResult OutRighttHit;
		//FTransform OutRightTansfrom;

		//GetMesh()->GetTransformAttribute_Ref(TEXT("foot_r"), ,OutRightTansfrom);

		//GetMesh()->Bodies[RightBone]->LineTrace(OutRighttHit, , , false, true);
	}
}

