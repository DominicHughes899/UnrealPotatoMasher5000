// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IngredientStateEnum.generated.h"

UENUM(BlueprintType)
enum class EIngredientName : uint8
{
	None,
	Carrot
};

UENUM(BlueprintType)
enum class EProcessedState : uint8
{
	Unprocessed,
	Chopped,
	Diced
};

UENUM(BlueprintType)
enum class ECookedState : uint8
{
	Raw,
	Boiled,
	Roasted,
	Fried
};

UENUM(BlueprintType)
enum class EPackagedType : uint8
{
	None,
	DicedCarrots
};