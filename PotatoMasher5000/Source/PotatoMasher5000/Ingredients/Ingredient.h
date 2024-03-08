// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../InteractionInterface.h"

#include "Ingredient.generated.h"

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
	void Focus() override;
	void UnFocus() override;
	FVector GetLocation() const override { return GetActorLocation(); }

protected:
	// ==== Component Setup ====
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	// UI





};
