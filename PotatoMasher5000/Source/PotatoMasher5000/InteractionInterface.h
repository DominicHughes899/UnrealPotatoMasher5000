// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Appliances/ApplianceFunctionEnum.h"

#include "InteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class POTATOMASHER5000_API IInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// ==== General ====
	UFUNCTION()
	virtual void Focus() {}

	UFUNCTION()
	virtual void UnFocus() {}

	UFUNCTION()
	virtual FVector GetLocation() const { return FVector::ZeroVector; }

	UFUNCTION()
	virtual float GetFunctionDuration() { return 0.f; }


	// ==== Ingredient ====
	UFUNCTION()
	virtual void OnPickUp() {}

	UFUNCTION()
	virtual void OnPutDown() {}

	UFUNCTION() 
	virtual void UpdateCurrentAppliance(AActor* NewAppliance) {}

	UFUNCTION()
	virtual AActor* GetCurrentAppliance() { return nullptr; }

	UFUNCTION()
	virtual bool CanStartInteraction() { return false; }

	UFUNCTION()
	virtual void CancelInteraction() {}

	UFUNCTION()
	virtual void TriggerInteraction() {}


	// ==== Appliance ====
	UFUNCTION()
	virtual USceneComponent* GetAttachComponent() { return nullptr; }

	UFUNCTION()
	virtual bool CanReceiveItem(AActor* ActorToReceive) { return false; }

	UFUNCTION()
	virtual void OnActorAttached(AActor* ActorAttacheed) {}

	UFUNCTION()
	virtual void OnActorDetached(AActor* ActorDetached) {}

	UFUNCTION()
	virtual EApplianceFunctionEnum GetApplianceFunction() { return EApplianceFunctionEnum::None; }



};
