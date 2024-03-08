// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../InteractionInterface.h"


#include "Appliance.generated.h"

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ==== Interface overrides ====

private:
	// ==== Component setup ====
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	USceneComponent* AttachLocationComponent;

	// ==== Item limit ====
	int ItemsAllowed = 1;
	int HeldItems = 0;

	// ==== Function ====

};
