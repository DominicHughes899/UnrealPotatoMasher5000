// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Appliance.h"

#include "../Ingredients/IngredientStruct.h"

#include "PackagingStation.generated.h"

/**
 * 
 */
UCLASS()
class POTATOMASHER5000_API APackagingStation : public AAppliance
{
	GENERATED_BODY()
	
public:
	APackagingStation();

	void BeginPlay() override;

	void OnActorAttached(AActor* ActorAttached) override;
	bool CanReceiveItem(AActor* ActorToReceive) override;

	// Prototyping
	UFUNCTION(BlueprintImplementableEvent)
	void PrintInfo(FIngredientStruct InfoToPrint);

private:

	void ResetActiveRecipe();
	bool CheckNeededForRecipe(const FIngredientStruct& IngredientToCheck);
	void SpawnPackagedFood();

	TArray<FIngredientStruct> OriginalRecipe;
	TArray<FIngredientStruct> ActiveRecipe;



};
