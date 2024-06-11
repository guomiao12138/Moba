// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityComponent.h"
#include "Ability/MobaAbility.h"
#include "Node/AbilityNode.h"
#include "Node/Root.h"

#include "GameFramework/Character.h"

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
	//TickAbility(DeltaTime);
}

void UMobaAbilityComponent::TickAbility(float DeltaTime)
{
	//if (CurrentAbility)
	//{
	//	CurrentAbility->RootNode->Tick(DeltaTime);
	//}
}

void UMobaAbilityComponent::ActiveAbility()
{
	if (Abilitys.Num() > 0)
	{
		Abilitys[0]->Owner = Cast<ACharacter>(GetOwner());
		Abilitys[0]->Activate();
	}
	//CurrentAbility->Owner = Cast<ACharacter>(GetOwner());
	//CurrentAbility->RootNode->OnActiveNode();
	//UAbilityNode* temp = CurrentAbility->RootNode;
	//UAbilityNode* pre = nullptr;

	//while (temp)
	//{
	//	if (temp->OnDeActiveNode())
	//	{
	//		if (UEdGraphPin* pin = temp->GetThenPin())
	//		{
	//			if (pin->LinkedTo.Num() > 0)
	//			{
	//				if (temp = Cast<UAbilityNode>(pin->LinkedTo[0]->GetOwningNode()))
	//				{
	//					temp->OnActiveNode();
	//				}
	//			}
	//			else
	//			{
	//				temp = nullptr;
	//			}
	//		}
	//		else
	//		{
	//			break;
	//		}
	//	}
	//	else
	//	{
	//		break;
	//	}
	//}
}

void UMobaAbilityComponent::SetCurrentAbility(UMobaAbility* InAbility)
{
	CurrentAbility = InAbility;
}

void UMobaAbilityComponent::ActiveNode(TArray<UEdGraphPin*> InPins)
{
	//for (auto pin : InPins)
	//{
	//	Cast<UAbilityNode>(pin->GetOwningNode())->OnActiveNode();
	//}
}

