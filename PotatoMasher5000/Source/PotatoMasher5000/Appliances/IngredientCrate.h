// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Appliance.h"

#include "IngredientCrate.generated.h"

class AIngredient;

/**
 * 
 */
UCLASS()
class POTATOMASHER5000_API AIngredientCrate : public AAppliance
{
	GENERATED_BODY()
	
public:
	AIngredientCrate();

	void BeginPlay() override;

private:
	
	void SpawnIngredients();

	UPROPERTY(EditAnywhere)
	int SpawnCount = 2;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AIngredient> IngredientType;
	

};
