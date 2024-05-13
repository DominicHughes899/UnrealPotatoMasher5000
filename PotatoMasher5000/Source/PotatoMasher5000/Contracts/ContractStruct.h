// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../Ingredients/IngredientStateEnum.h"

#include "ContractStruct.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FContractStruct
{
	GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    EPackagedType PackageType = EPackagedType::None;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    int QuantityRequired = 0;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    int QuantityDelivered = 0;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    int Reward = 0;
	
};