// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../InteractionInterface.h"

#include "ApplianceFunctionEnum.h"


#include "Appliance.generated.h"

class USpringArmComponent;
class UWidgetComponent;
class UApplianceInteractionPromptUI;

UCLASS()
class POTATOMASHER5000_API AAppliance : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAppliance();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ==== Component setup ====
	// Mesh
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	// SceneComp
	UPROPERTY(EditAnywhere)
	USceneComponent* AttachLocationComponent;

	// UI
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* PromptBoom;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* InteractionUIComponent;

	UPROPERTY(EditAnywhere)
	UApplianceInteractionPromptUI* InteractionUI;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UApplianceInteractionPromptUI> UIClassRef;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ==== Interface overrides ====
	// General
	void Focus() override;
	void UnFocus() override;
	FVector GetLocation() const override { return GetActorLocation(); }
	float GetFunctionDuration() override { return FunctionDuration; }

	// Appliance
	USceneComponent* GetAttachComponent() { return AttachLocationComponent; }
	bool CanReceiveItem(AActor* ActorToReceive) override;
	void OnActorAttached(AActor* ActorAttached) override;
	void OnActorDetached(AActor* ActorDetached) override;


	EApplianceFunctionEnum GetApplianceFunction() override { return ApplianceFunction; } // Called from Ingredient.h



protected:
	// ==== Item limit ====
	int ItemsAllowed = 1;
	int HeldItems = 0;

	// ==== Function ====
	float FunctionDuration = 1.f;
	EApplianceFunctionEnum ApplianceFunction = EApplianceFunctionEnum::None;
	EApplianceName ApplianceName = EApplianceName::Counter;

};
