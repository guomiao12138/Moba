// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MobaCharacterBase.generated.h"

class AMobaPlayerController;

UCLASS()
class MOBA_API AMobaCharacterBase : public ACharacter
{
	GENERATED_BODY()

protected:
	int LeftBone = -1;
	int RightBone = -1;

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AMobaPlayerController> MobaPlayerController;


	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<class UMobaAbilityComponent> AbilityComponent;


public:
	// Sets default values for this character's properties
	AMobaCharacterBase();
	void InitController(AMobaPlayerController* InController);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ActiveAbility();
	void MoveTo(FVector InLocation);
	void UpdateBoneIndex();
	void UpdatePlayFootHit();
};
