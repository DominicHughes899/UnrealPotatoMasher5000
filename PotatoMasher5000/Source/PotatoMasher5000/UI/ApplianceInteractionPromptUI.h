// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "../Appliances/ApplianceFunctionEnum.h"
#include "../Ingredients/RecipeStruct.h"

#include "ApplianceInteractionPromptUI.generated.h"

/**
 * 
 */
UCLASS()
class POTATOMASHER5000_API UApplianceInteractionPromptUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetTitle(EApplianceName NewTitle);

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerFocus();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerUnfocus();

	UFUNCTION(BlueprintImplementableEvent)
	void AccessDenied();

	// Packaging Station Only
	UFUNCTION(BlueprintImplementableEvent)
	void SetRecipe();

	UFUNCTION(BlueprintImplementableEvent)
	void ResetRecipe();

	UFUNCTION(BlueprintImplementableEvent)
	void AppendRecipe(int Number, FIngredientStruct Ingredient);

	UFUNCTION(BlueprintImplementableEvent)
	void FinaliseRecipe();
};
