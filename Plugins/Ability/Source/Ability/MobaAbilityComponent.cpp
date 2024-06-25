// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityComponent.h"
#include "Ability/MobaAbility.h"
#include "Node/AbilityNode.h"
#include "Node/Root.h"

#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

// Sets default values for this component's properties
UMobaAbilityComponent::UMobaAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...


}


// Called when the game starts
void UMobaAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (auto Pawn = Cast<APawn>(GetOwner()))
	{
		if (SkeletalMeshComponent = Pawn->FindComponentByClass<USkeletalMeshComponent>())
		{
			if (auto AnimInstance = SkeletalMeshComponent->GetAnimInstance())
			{
				AnimInstance->OnMontageStarted.AddDynamic(this, &UMobaAbilityComponent::OnStartMontage);
				AnimInstance->OnMontageEnded.AddDynamic(this, &UMobaAbilityComponent::OnEndMontage);
			}
		}
	}
}


// Called every frame
void UMobaAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//TickAbility(DeltaTime);


}

void UMobaAbilityComponent::TickAbility(float DeltaTime)
{
	//if (CurrentAbility)
	//{
	//	CurrentAbility->RootNode->Tick(DeltaTime);
	//}
}

void UMobaAbilityComponent::OnStartMontage(UAnimMontage* Montage)
{
	if (AnimMontages.Contains(Montage))
	{
		OnMontageStarted.Broadcast(AnimMontages[Montage].Tags, CurrentAbility->EnableCollision);
	}
}

void UMobaAbilityComponent::OnEndMontage(UAnimMontage* Montage, bool bInterrupted)
{
	if (AnimMontages.Contains(Montage))
	{
		OnMontageFinish.Broadcast(AnimMontages[Montage].Tags);
		AnimMontages.Remove(Montage);
	}
}

void UMobaAbilityComponent::PlayAnimation(class UAnimSequenceBase* Asset, TArray<FGameplayTag> Tags)
{
	if (auto Pawn = Cast<APawn>(GetOwner()))
	{
		if (UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance())
		{
			auto Montage = AnimInstance->PlaySlotAnimationAsDynamicMontage(Asset, TEXT("Active"));
			Montage->SyncGroup = TEXT("Ability");

			if (!AnimMontages.Contains(Montage))
			{
				AnimMontages.Emplace(Montage, FAbilityTag(Tags));
			}
		}
	}
}

void UMobaAbilityComponent::ActiveAbility()
{
	if (Abilitys.Num() > 0)
	{
		Abilitys[0]->Owner = Cast<ACharacter>(GetOwner());
		Abilitys[0]->Activate();
	}
}

void UMobaAbilityComponent::FinishAbility()
{
}

void UMobaAbilityComponent::SetCurrentAbility(UMobaAbility* InAbility)
{
	CurrentAbility = InAbility;
}

void UMobaAbilityComponent::ActiveNode(TArray<UEdGraphPin*> InPins)
{

}

