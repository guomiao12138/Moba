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





public:
#if WITH_EDITORONLY_DATA
	UPROPERTY()
	class UMobaAbilityEdGraph* Graph;

#endif

	UPROPERTY()
	TObjectPtr<class UAbilityNode> RootNode;

	UPROPERTY()
	TObjectPtr<APawn> Owner;

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

	//void SetGraph(UMobaAbilityEdGraph* InGraph) { Graph = InGraph; }
	//UMobaAbilityEdGraph* GetGraph() { return Graph; }
	


	static UMobaAbility* SpawnAbility(FVector InLocation);
};
