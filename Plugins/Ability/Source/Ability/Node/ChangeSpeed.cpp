// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeSpeed.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

//void UChangeSpeed::AllocateDefaultPins()
//{
//}
#if WITH_EDITOR
FText UChangeSpeed::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString("ChangeSpeed");
}
#endif	
void UChangeSpeed::OnActiveNode()
{
	Super::OnActiveNode();
	//UE_LOG(LogTemp, Display, TEXT("OnActiveNode  %f"), DuringTime);
	OldSpeed = Cast<ACharacter>(GetOwnerPawn())->GetCharacterMovement()->MaxWalkSpeed;

	if (auto ac = GetOwnerPawn())
	{
		if (auto moveCom = Cast<ACharacter>(ac)->GetCharacterMovement())
		{
			moveCom->MaxWalkSpeed = Speed;
		}
	}
}

bool UChangeSpeed::OnDeActiveNode()
{
	if (auto ac = GetOwnerPawn())
	{
		if (auto moveCom = Cast<ACharacter>(ac)->GetCharacterMovement())
		{
			moveCom->MaxWalkSpeed = OldSpeed;
		}
	}

	UE_LOG(LogTemp, Display, TEXT("OnDeActiveNode"));
	return true;
}

void UChangeSpeed::Tick(float DeltaTime)
{

}
