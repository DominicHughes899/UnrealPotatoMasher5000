// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../InteractionInterface.h"
#include "IngredientStruct.h"

#include "Ingredient.generated.h"

class USpringArmComponent;
class UWidgetComponent;
class UInteractionPromptUI;

UCLASS()
class POTATOMASHER5000_API AIngredient : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIngredient();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ==== Interface overrides ====
	// General
	void Focus() override;
	void UnFocus() override;
	FVector GetLocation() const override { return GetActorLocation(); }
	float GetFunctionDuration() override;

	// Ingredient
	void OnPickUp() override;
	void OnPutDown() override;
	void UpdateCurrentAppliance(AActor* NewAppliance) override { CurrentAppliance = NewAppliance;  CurrentApplianceInterface = Cast<IInteractionInterface>(CurrentAppliance); }
	AActor* GetCurrentAppliance() override { return CurrentAppliance; }
	bool CanStartInteraction() override;
	void CancelInteraction() override;
	FIngredientStruct GetIngredientInformation() override { return IngredientInformation; }


protected:
	// ==== Component Setup ====
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	// UI
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* PromptBoom;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* InteractionUIComponent;

	UPROPERTY(EditAnywhere)
	UInteractionPromptUI* InteractionUI;

	// ==== Interactions ====
	UPROPERTY(EditAnywhere)
	TArray<EApplianceFunctionEnum> AllowedFunctions;

	void LockInteraction();
	bool CanInteract = true;

	// ==== Current Appliance ====

	AActor* CurrentAppliance = nullptr;
	IInteractionInterface* CurrentApplianceInterface = nullptr;

	// ==== Ingredient State ====
	FIngredientStruct IngredientInformation;

	// ==== Packaged Only ====
	EPackagedType PackagedType = EPackagedType::None;

private:









};
