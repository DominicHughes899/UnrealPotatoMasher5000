// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Appliance.h"

#include "../Ingredients/IngredientStruct.h"
#include "../Ingredients/RecipeStruct.h"

#include "PackagingStation.generated.h"


class UBoxComponent;
/**
 * 
 */
UCLASS()
class POTATOMASHER5000_API APackagingStation : public AAppliance
{
	GENERATED_BODY()
	
public:
	APackagingStation();

	void BeginPlay() override;

	void OnActorAttached(AActor* ActorAttached) override;
	bool CanReceiveItem(AActor* ActorToReceive) override;

	// Prototyping
	UFUNCTION(BlueprintImplementableEvent)
	void PrintInfo(FIngredientStruct InfoToPrint);

protected:

	// Extra Components
	// Proximity Detection Box
	UPROPERTY(EditAnywhere)
	UBoxComponent* ProximityDetectionBox;

private:
	// Interface overrides
	void Focus() override { MeshComponent->SetRenderCustomDepth(true); }
	void UnFocus() override { MeshComponent->SetRenderCustomDepth(false); }

	// Custom overlap function for UI 
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	// ==== Packaging ====
	void ResetActiveRecipe();
	bool CheckNeededForRecipe(const FIngredientStruct& IngredientToCheck);
	void SpawnPackagedFood();
	void UpdateUI();

	FRecipeStruct OriginalRecipe;
	FRecipeStruct ActiveRecipe;

	
	//TArray<FIngredientStruct> OriginalRecipe;
	//TArray<FIngredientStruct> ActiveRecipe;

	



};
