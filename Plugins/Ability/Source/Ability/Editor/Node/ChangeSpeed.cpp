// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeSpeed.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

//void UChangeSpeed::AllocateDefaultPins()
//{
//}

FText UChangeSpeed::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString("ChangeSpeed");
}

void UChangeSpeed::OnActiveNode()
{
	Super::OnActiveNode();
	//UE_LOG(LogTemp, Display, TEXT("OnActiveNode  %f"), DuringTime);
	OldSpeed = Cast<ACharacter>(GetOwnerPawn())->GetCharacterMovement()->MaxWalkSpeed;
}

bool UChangeSpeed::OnDeActiveNode()
{

	UE_LOG(LogTemp, Display, TEXT("OnDeActiveNode"));
	return true;
}

void UChangeSpeed::Tick(float DeltaTime)
{
	DuringTime -= DeltaTime;
	UE_LOG(LogTemp, Display, TEXT("OnActiveNode  %f"));

	if (auto ac = GetOwnerPawn())
	{
		if (auto moveCom = Cast<ACharacter>(ac)->GetCharacterMovement())
		{
			if (DuringTime > 0)
			{
				moveCom->MaxWalkSpeed = Speed;
			}
			else
			{
				moveCom->MaxWalkSpeed = OldSpeed;
			}
		}
	}
}
