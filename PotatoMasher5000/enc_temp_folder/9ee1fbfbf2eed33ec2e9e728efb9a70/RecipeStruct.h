// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IngredientStruct.h"

#include "RecipeStruct.generated.h"
/**
 * 
 */
class POTATOMASHER5000_API RecipeStruct
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FIngredientStruct> Ingredients;

	UPROPERTY()
	EPackagedType PackagedType;

};
