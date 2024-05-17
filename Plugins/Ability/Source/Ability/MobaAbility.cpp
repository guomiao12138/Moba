// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbility.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
UMobaAbility::UMobaAbility()
{
	//Mesh = 
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube"));
	Mesh->SetStaticMesh(Cube.Object);

}

void UMobaAbility::Activate()
{
	//Super::ProcessEvent(FindFunctionChecked(FName(TEXT("Start"))), NULL);

}
