// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MobaAbility.generated.h"

/**
 * 
 */
UCLASS()
class ABILITY_API UMobaAbility : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY(SaveGame)
	class UMobaAbilityEdGraph* Graph;

	TObjectPtr<APawn> Owner;

public:
	//virtual void ProcessEvent(UFunction* Function, void* Parms) override;

	void Activate();

	UPROPERTY(EditAnywhere)
	FName AbilityName;

	UFUNCTION(BlueprintImplementableEvent)
	void Start();
	

	UFUNCTION(BlueprintCallable)
	void AAAA(FName name, int& num);

	UFUNCTION()
	void CCCC(UAnimationAsset* asset);

	UFUNCTION()
	void XXXX();

	UMobaAbilityEdGraph* SetGraph(UMobaAbilityEdGraph* InGraph) { return Graph = InGraph; }
	UMobaAbilityEdGraph* GetGraph() { return Graph; }
	APawn* GetOwner() { return Owner; }

};
