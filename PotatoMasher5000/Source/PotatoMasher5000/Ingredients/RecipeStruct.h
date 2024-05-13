// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IngredientStruct.h"

#include "RecipeStruct.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct FRecipeStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<FIngredientStruct> Ingredients;

	UPROPERTY(BlueprintReadOnly)
	EPackagedType PackagedType;

};
