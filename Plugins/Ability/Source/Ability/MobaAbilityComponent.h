// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "MobaAbilityComponent.generated.h"

class UMobaAbility;
class UAnimMontage;
struct FGameplayTag;

USTRUCT()
struct FAbilityTag
{
	GENERATED_USTRUCT_BODY()


	FAbilityTag() {};
	FAbilityTag(TArray<FGameplayTag> InTags) : Tags(InTags) {};

	~FAbilityTag() {};

	TArray<FGameplayTag> Tags;
};

UCLASS( ClassGroup=(MobaAbility), meta=(BlueprintSpawnableComponent) )
class ABILITY_API UMobaAbilityComponent : public UActorComponent
{
	GENERATED_BODY()
private:

	UPROPERTY()
	TObjectPtr<UMobaAbility> CurrentAbility;

	UPROPERTY()
	TMap<TObjectPtr<UAnimMontage>, FAbilityTag> AnimMontages;

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UFUNCTION()
	void OnStartMontage(UAnimMontage* Montage);

	UFUNCTION()
	void OnEndMontage(UAnimMontage* Montage, bool bInterrupted);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:	

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMontageStartedDelegate, TArray<FGameplayTag>, Tag, bool, EnableCollision);
	FOnMontageStartedDelegate OnMontageStarted;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMontageFinishDelegate, TArray<FGameplayTag>, Tag);
	FOnMontageFinishDelegate OnMontageFinish;
	// Sets default values for this component's properties
	UMobaAbilityComponent();

	// Called every frame

	void TickAbility(float DeltaTime);

	UPROPERTY(EditAnywhere, Category = "Ability")
	TArray<UMobaAbility*> Abilitys;

	void PlayAnimation(class UAnimSequenceBase* Asset, TArray<FGameplayTag> Tags);
	void ActiveAbility();
	void FinishAbility();

	void SetCurrentAbility(UMobaAbility* InAbility);

	void ActiveNode(TArray<class UEdGraphPin*> InPins);
};
