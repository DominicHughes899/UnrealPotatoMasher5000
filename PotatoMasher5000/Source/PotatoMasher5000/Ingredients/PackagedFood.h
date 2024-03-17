// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ingredient.h"



#include "PackagedFood.generated.h"

/**
 * 
 */
UCLASS()
class POTATOMASHER5000_API APackagedFood : public AIngredient
{
	GENERATED_BODY()
	
public:
	APackagedFood();

	EPackagedType GetPackagedType() { return PackagedType; }
	void SetPackagedType(EPackagedType NewType) { PackagedType = NewType; }

private:
	

};
