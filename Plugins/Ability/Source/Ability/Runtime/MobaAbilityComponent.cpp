// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityComponent.h"
#include "Ability/Runtime/MobaAbility.h"
#include "Ability/Editor/Node/AbilityNode.h"

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
	
}


// Called every frame
void UMobaAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	TickAbility(DeltaTime);
}

void UMobaAbilityComponent::TickAbility(float DeltaTime)
{
	if (CurrentAbility)
	{
		CurrentAbility->RootNode->Tick(DeltaTime);
	}
}

void UMobaAbilityComponent::ActiveAbility()
{
	CurrentAbility->Owner = Cast<APawn>(GetOwner());
	CurrentAbility->RootNode->OnActiveNode();
	UAbilityNode* temp = CurrentAbility->RootNode;
	UAbilityNode* pre = nullptr;

	while (temp)
	{
		if (temp->OnDeActiveNode())
		{
			if (UEdGraphPin* pin = temp->GetThenPin())
			{
				temp = Cast<UAbilityNode>(pin->GetOwningNode());
				temp->OnActiveNode();
			}
		}
	}
}

void UMobaAbilityComponent::SetCurrentAbility(UMobaAbility* InAbility)
{
	CurrentAbility = InAbility;
}

void UMobaAbilityComponent::ActiveNode(TArray<UEdGraphPin*> InPins)
{
	for (auto pin : InPins)
	{
		Cast<UAbilityNode>(pin->GetOwningNode())->OnActiveNode();
	}
}

