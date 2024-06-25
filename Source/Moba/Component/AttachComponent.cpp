// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachComponent.h"
#include "Engine/TriggerBase.h"
#include "Components/ShapeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Moba/Damage/MobaDamageType.h"


void UWeaponCollisionComponent::ActiveCollision()
{
	if (auto Actor = Cast<ATriggerBase>(GetChildActor()))
	{
		if (Actor->GetCollisionComponent())
		{
			Actor->GetCollisionComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			Actor->GetCollisionComponent()->SetGenerateOverlapEvents(true);
			Actor->GetCollisionComponent()->SetNotifyRigidBodyCollision(true);
		}
	}
}

void UWeaponCollisionComponent::CloseCollision()
{
	if (auto Actor = Cast<ATriggerBase>(GetChildActor()))
	{
		if (Actor->GetCollisionComponent())
		{
			Actor->GetCollisionComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Actor->GetCollisionComponent()->SetGenerateOverlapEvents(false);
			Actor->GetCollisionComponent()->SetNotifyRigidBodyCollision(false);
		}
	}
}

void UWeaponCollisionComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::ApplyDamage(Other, 20.f, Cast<APawn>(GetOwner())->GetController(), GetOwner(), UMobaDamageType::StaticClass());
}

void UWeaponCollisionComponent::CreateChildActor(TFunction<void(AActor*)> CustomizerFunc)
{
	Super::CreateChildActor(CustomizerFunc);

	if (auto Actor = Cast<ATriggerBase>(GetChildActor()))
	{
		if (Actor->GetCollisionComponent())
		{
			Actor->GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &UWeaponCollisionComponent::OnBeginOverlap);
			Actor->GetCollisionComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}
