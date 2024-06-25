// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MobaAbility.generated.h"

/**
 * 
 */
class UAnimationAsset;
class URoot;
class ACharacter;

UCLASS(BlueprintType)
class ABILITY_API UMobaAbility : public UObject
{
	GENERATED_BODY()

private:
	class UStaticMeshComponent* Mesh;





public:
#if WITH_EDITORONLY_DATA
	UPROPERTY()
	TObjectPtr<class UEdGraph> Graph;

#endif

	UPROPERTY()
	TObjectPtr<URoot> RootNode;

	UPROPERTY()
	TObjectPtr<APawn> Owner;

	UMobaAbility();

	void Activate();

	UPROPERTY(EditAnywhere)
	FName AbilityName;

	UPROPERTY(EditAnywhere)
	bool EnableCollision = false;

	
	//void SetGraph(UMobaAbilityEdGraph* InGraph) { Graph = InGraph; }
	//UMobaAbilityEdGraph* GetGraph() { return Graph; }
	


	static UMobaAbility* SpawnAbility(FVector InLocation);
};
