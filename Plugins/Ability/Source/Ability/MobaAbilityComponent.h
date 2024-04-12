// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MobaAbilityComponent.generated.h"

class UMobaAbility;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABILITY_API UMobaAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	UMobaAbility* CurrentAbility;

public:	
	// Sets default values for this component's properties
	UMobaAbilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void TickAbility(float DeltaTime);

	UPROPERTY(EditAnywhere)
	TArray<UMobaAbility*> Abilitys;


	//void ActiveNode();
		
	void ActiveAbility();
	void SetCurrentAbility(UMobaAbility* InAbility);
	void ActiveNode(TArray<UEdGraphPin*> InPins);
};
