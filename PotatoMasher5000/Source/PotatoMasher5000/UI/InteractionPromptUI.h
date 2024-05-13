// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "../Appliances/ApplianceFunctionEnum.h"
#include "../Ingredients/IngredientStruct.h"

#include "InteractionPromptUI.generated.h"

/**
 * 
 */
UCLASS()
class POTATOMASHER5000_API UInteractionPromptUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerFocus(bool InteractVisible, EApplianceFunctionEnum ApplianceFunction, FIngredientStruct IngredientInformation, EPackagedType PackagedType);

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerUnfocus();

	UFUNCTION(BlueprintImplementableEvent)
	void OnIngredientLocked();
};
