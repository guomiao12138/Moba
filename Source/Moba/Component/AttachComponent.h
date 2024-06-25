// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ChildActorComponent.h"
#include "AttachComponent.generated.h"

/**
 * 
 */
UCLASS()
class MOBA_API UAttachComponent : public UChildActorComponent
{
	GENERATED_BODY()
	
};

UCLASS(meta = (BlueprintSpawnableComponent))
class MOBA_API UWeaponCollisionComponent : public UAttachComponent
{
	GENERATED_BODY()

public:

	void ActiveCollision();
	void CloseCollision();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void CreateChildActor(TFunction<void(AActor*)> CustomizerFunc = nullptr) override;
};
