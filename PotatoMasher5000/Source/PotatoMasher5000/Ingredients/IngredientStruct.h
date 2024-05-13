// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IngredientStateEnum.h"

#include "IngredientStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FIngredientStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EIngredientName Name = EIngredientName::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EProcessedState ProcessedState = EProcessedState::Unprocessed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECookedState CookedState = ECookedState::Raw;
};