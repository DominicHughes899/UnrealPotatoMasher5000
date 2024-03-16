// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ApplianceFunctionEnum.generated.h"

UENUM(BlueprintType)
enum class EApplianceFunctionEnum : uint8
{
	None,
	Cut,
	Roast,
	Boil
};

UENUM(BlueprintType)
enum class EApplianceName : uint8
{
	Counter,
	CuttingStation,
	OvenStation,
	BoilingStation,
	PackagingStation,
	Bin,
	IngredientCrate

};