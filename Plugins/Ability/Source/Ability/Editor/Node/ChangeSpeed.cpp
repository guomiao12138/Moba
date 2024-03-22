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
	UE_LOG(LogTemp, Display, TEXT("OnActiveNode  %f"), DuringTime);
	OldSpeed = Cast<ACharacter>(GetOwnerPawn())->GetCharacterMovement()->Velocity;
}

bool UChangeSpeed::OnDeActiveNode()
{
	UE_LOG(LogTemp, Display, TEXT("OnDeActiveNode"));
	return false;
}

void UChangeSpeed::Tick(float DeltaTime)
{
	DuringTime -= DeltaTime;

	if (auto ac = GetOwnerPawn())
	{
		if (auto moveCom = Cast<ACharacter>(ac)->GetCharacterMovement())
		{
			if (DuringTime > 0)
			{
				FVector cur = moveCom->Velocity.GetSafeNormal();
				moveCom->Velocity = cur * Speed;
			}
			else
			{
				moveCom->Velocity = OldSpeed;
			}
		}
	}
}
