// Fill out your copyright notice in the Description page of Project Settings.


#include "Ingredient.h"

// Sets default values
AIngredient::AIngredient()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);



}

// Called when the game starts or when spawned
void AIngredient::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIngredient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIngredient::Focus()
{
	MeshComponent->SetRenderCustomDepth(true);

	// UI etc.
}

void AIngredient::UnFocus()
{
	MeshComponent->SetRenderCustomDepth(false);

	// UI etc.
}

