// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Moba/Logic/MobaEnum.h"
#include "MobaCharacterBase.generated.h"

class AMobaPlayerController;
class UTextureRenderTarget2D;
class UMaterialInstanceDynamic;
class UMaterialInterface;
class UMobaAbilityComponent;
class UBoxComponent;
struct FGameplayTag;
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
	TObjectPtr<UMobaAbilityComponent> AbilityComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> Canvan_Interface;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> Location_Interface;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> Canvan_Mat;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> Location_Mat;


	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextureRenderTarget2D> Location_RT;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextureRenderTarget2D> Canvas_RT;

	UPROPERTY(EditAnywhere)
	float Radius = 0.f;	
	
	UPROPERTY(EditAnywhere)
	bool DrawViewPath = false;

	UPROPERTY(EditAnywhere)
	float AttackDistance = 100.f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponCollision")
	TArray<TSubclassOf<UShapeComponent>> WeaponCollisions;
public:
	// Sets default values for this character's properties
	AMobaCharacterBase();

	UFUNCTION()
	void OnAbilityStart(TArray<FGameplayTag> InTags, bool EnableCollision);

	UFUNCTION()
	void OnAbilityFinish(TArray<FGameplayTag> InTags);

	void InitController(AMobaPlayerController* InController);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void OnDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	void ChangeState(ECharacterType::Type Type);
	void ActiveActiveCollision();
	void CloseActiveCollision();
	void ActiveAbility();
	void MoveTo(FHitResult Hit);
	void UpdateBoneIndex();
	void UpdatePlayFootHit();

	void UpdateRT();
};
