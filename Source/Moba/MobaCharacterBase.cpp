// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaCharacterBase.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "PhysicsEngine/PhysicsAsset.h"
#include "Materials/MaterialInstance.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "KismetTraceUtils.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayTagContainer.h"

#include "MobaPlayerController.h"
#include "Ability/MobaAbilityComponent.h"
#include "Component/AttachComponent.h"
#include "Moba/Animation/MobaAnimInstance.h"



// Sets default values
AMobaCharacterBase::AMobaCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//GetMesh()->SetSkeletalMeshAsset();

	AbilityComponent = CreateDefaultSubobject<UMobaAbilityComponent>(TEXT("AbilityComponent"));

	//GetMesh()->SetSimulatePhysics(true);
	if (AbilityComponent)
	{
		AbilityComponent->OnMontageStarted.AddDynamic(this, &AMobaCharacterBase::OnAbilityStart);
		AbilityComponent->OnMontageFinish.AddDynamic(this, &AMobaCharacterBase::OnAbilityFinish);
	}
}

void AMobaCharacterBase::OnAbilityStart(TArray<FGameplayTag> InTags, bool EnableCollision)
{
	for (FGameplayTag Tag : InTags)
	{

	}

	if (EnableCollision)
	{
		ActiveCollision();
	}
}

void AMobaCharacterBase::OnAbilityFinish(TArray<FGameplayTag> InTags)
{
	for (FGameplayTag Tag : InTags)
	{

	}
	ChangeState(ECharacterType::Idle);
	CloseActiveCollision();
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

	Canvan_Mat = UMaterialInstanceDynamic::Create(Canvan_Interface, GetWorld(), TEXT("Canvan_Mat"));
	Location_Mat = UMaterialInstanceDynamic::Create(Location_Interface, GetWorld(), TEXT("Location_Mat"));
	UKismetRenderingLibrary::ClearRenderTarget2D(this, Canvas_RT);
	UKismetRenderingLibrary::ClearRenderTarget2D(this, Location_RT);



}

// Called every frame
void AMobaCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UpdatePlayFootHit();

	UpdateRT();
}

// Called to bind functionality to input
void AMobaCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//CharacterMovement->MoveUpdatedComponent();
}

float AMobaCharacterBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ResultDamage =  Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	OnDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	return ResultDamage;
}

void AMobaCharacterBase::OnDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Display, TEXT("Damage : %f"), Damage);
}

void AMobaCharacterBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AMobaCharacterBase, WeaponCollisions))
	{

	}

}

void AMobaCharacterBase::ChangeState(ECharacterType::Type Type)
{
	if (auto Instance = Cast<UMobaAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		Instance->SetChangeState(Type);
	}
}

void AMobaCharacterBase::ActiveCollision()
{
	for (auto Com : GetMesh()->GetAttachChildren())
	{
		//if (Com->ComponentTags.Contains(TEXT("WeaponCollision")))
		{
			if (auto WeaponCollisionComponent = Cast<UWeaponCollisionComponent>(Com))
			{
				WeaponCollisionComponent->ActiveCollision();
			}
		}
	}
}

void AMobaCharacterBase::CloseActiveCollision()
{
	for (auto Com : GetMesh()->GetAttachChildren())
	{
		//if (Com->ComponentTags.Contains(TEXT("WeaponCollision")))
		{
			if (auto WeaponCollisionComponent = Cast<UWeaponCollisionComponent>(Com))
			{
				WeaponCollisionComponent->CloseCollision();
			}
		}
	}
}

void AMobaCharacterBase::ActiveAbility()
{
	if (GetMesh())
	{
		if (auto inst = Cast<UMobaAnimInstance>(GetMesh()->AnimScriptInstance))
		{
			ActiveCollision();
			inst->SetChangeState(ECharacterType::Skill);
			AbilityComponent->ActiveAbility();
			//CloseActiveCollision();
		}
	}
}

void AMobaCharacterBase::MoveTo(FHitResult Hit)
{

	DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 20.f, FColor::Blue, false, 10);

	DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), Hit.ImpactPoint, 20.f, FColor::Blue, false, 10.f);

	FVector dir = Hit.Location - GetActorLocation();
	SetActorRelativeRotation(FRotator(0, dir.Rotation().Yaw, 0));

	if (auto Pawn = Cast<APawn>(Hit.GetActor()))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), Hit.GetActor());
	}
	else
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), Hit.Location);
	}
}

void AMobaCharacterBase::UpdateBoneIndex()
{
	if (GetMesh())
	{
		RightBone = GetMesh()->GetPhysicsAsset()->FindBodyIndex(TEXT("foot_r"));
		LeftBone = GetMesh()->GetPhysicsAsset()->FindBodyIndex(TEXT("foot_l"));
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
			//GetMesh()->GetBoneLocation();
			Location = GetMesh()->GetBoneLocation(TEXT("foot_l"));
			//UE_LOG(LogTemp, Warning, TEXT("OutLeftTansfrom : %s"), *OutLeftTansfrom.GetLocation().ToString());
			FVector End = FVector(0, 0, -1) * 1000 + Location;
			//Fcollsio
			//bool LeftHit = GetWorld()->LineTraceSingleByChannel(OutLeftHit, Location, End, ECollisionChannel:);
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(this);
			Params.bReturnPhysicalMaterial = true;
			//bool LeftHit = GetMesh()->LineTraceComponent(OutLeftHit, Location, End, Params);
			//DrawDebugLine(GetWorld(), Location, End, FColor::Black, false, -1, 0, 10);
			bool LeftHit = GetWorld()->LineTraceSingleByChannel(OutLeftHit, Location, End, ECollisionChannel::ECC_WorldStatic, Params);
			if (LeftHit)
			{
				//UE_LOG(LogTemp, Warning, TEXT("OutLeftTansfrom : %f"), OutLeftHit.Distance);
			}
		}
		//FHitResult OutRighttHit;
		//FTransform OutRightTansfrom;

		//GetMesh()->GetTransformAttribute_Ref(TEXT("foot_r"), ,OutRightTansfrom);

		//GetMesh()->Bodies[RightBone]->LineTrace(OutRighttHit, , , false, true);
	}
}

void AMobaCharacterBase::UpdateRT()
{
	UKismetRenderingLibrary::ClearRenderTarget2D(this, Canvas_RT);

	FVector Start = GetActorLocation();
	FVector End = Start + FVector(0, 0, 800);
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.bTraceComplex = true;
	Params.bReturnFaceIndex = true;
	bool Hit = GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius), Params);
	//bool Hit = UKismetSystemLibrary::SphereTraceSingle(this, Start, End, Radius, ETraceTypeQuery::TraceTypeQuery3, true, TArray<AActor*>(), EDrawDebugTrace::ForOneFrame, HitResult, true, FColor::Green, FColor::Red);
	
	if (Hit)
	{
		int32 UVChannel = 0;
		FVector2D UV;
		if (UGameplayStatics::FindCollisionUV(HitResult, UVChannel, UV))
		{
			Canvan_Mat->SetVectorParameterValue(TEXT("Location"), FVector(UV.X, UV.Y, 0));
			UKismetRenderingLibrary::DrawMaterialToRenderTarget(GetWorld(), Canvas_RT, Canvan_Mat);

			if (DrawViewPath)
			{
				Location_Mat->SetVectorParameterValue(TEXT("Location"), FVector(UV.X, UV.Y, 0));
				UKismetRenderingLibrary::DrawMaterialToRenderTarget(GetWorld(), Location_RT, Location_Mat);
			}
		}
	}
#if ENABLE_DRAW_DEBUG
	DrawDebugSphereTraceSingle(GetWorld(), Start, End, Radius, EDrawDebugTrace::ForOneFrame, Hit, HitResult, FColor::Green, FColor::Red, 0.f);
#endif


}

