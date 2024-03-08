// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ingredient.generated.h"

UCLASS()
class POTATOMASHER5000_API AIngredient : public AActor
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

protected:
	// ==== Component Setup ====
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	// UI

	// ==== Interface overrides ====



};
