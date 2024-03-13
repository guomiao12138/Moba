// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MobaAbility.generated.h"

/**
 * 
 */
class UAnimationAsset;

UCLASS(BlueprintType)
class ABILITY_API UMobaAbility : public UObject
{
	GENERATED_BODY()

private:
	class UStaticMeshComponent* Mesh;

	UPROPERTY()
	class UMobaAbilityEdGraph* Graph;

	TObjectPtr<APawn> Owner;

public:
	UMobaAbility();

	void Activate();

	UPROPERTY(EditAnywhere)
	FName AbilityName;

	UFUNCTION(BlueprintImplementableEvent)
	void Start();
	

	UFUNCTION(BlueprintCallable)
	void AAAA(FName name);

	UFUNCTION()
	void CCCC(UAnimationAsset* asset);

	UFUNCTION()
	void XXXX();

	UMobaAbilityEdGraph* SetGraph(UMobaAbilityEdGraph* InGraph) { return Graph = InGraph; }
	UMobaAbilityEdGraph* GetGraph() { return Graph; }
	APawn* GetOwner() { return Owner; }

	static UMobaAbility* SpawnAbility(FVector InLocation);
};
