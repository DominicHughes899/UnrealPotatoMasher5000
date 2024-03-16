// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ingredient.h"
#include "Carrot.generated.h"

/**
 * 
 */
UCLASS()
class POTATOMASHER5000_API ACarrot : public AIngredient
{
	GENERATED_BODY()
	
public:
	ACarrot();

private:
	// ==== Static Meshes ====
	UStaticMesh* UnprocessedMesh;
	UStaticMesh* ChoppedMesh;
	UStaticMesh* DicedMesh;

public:
	void TriggerInteraction() override;

private:
	// ==== Interaction handlers ====
	void Interaction_Cut();
	void Interaction_Roast();
	void Interaction_Boil();

};
