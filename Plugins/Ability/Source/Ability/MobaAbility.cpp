// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbility.h"
#include "MobaAbilityEdGraph.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
UMobaAbility::UMobaAbility()
{
	//Mesh = 
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
	Mesh->SetStaticMesh(Cube.Object);

}

void UMobaAbility::Activate()
{
	//Super::ProcessEvent(FindFunctionChecked(FName(TEXT("Start"))), NULL);
	if (Graph)
	{
		Graph->ActiveEventNode(TEXT("Start"));
	}
}

void UMobaAbility::AAAA(/*FName name, int& num*/)
{
	UE_LOG(LogTemp, Display, TEXT("UMobaAbility::AAAA"));
}

void UMobaAbility::CCCC(/*UAnimationAsset* asset*/)
{
	UE_LOG(LogTemp, Display, TEXT("UMobaAbility::CCCC"));
}

void UMobaAbility::XXXX()
{
	UE_LOG(LogTemp, Display, TEXT("UMobaAbility::XXXX"));
}
