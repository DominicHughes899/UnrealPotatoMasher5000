// Fill out your copyright notice in the Description page of Project Settings.


#include "IngredientCrate.h"

#include "../Ingredients/Ingredient.h"

AIngredientCrate::AIngredientCrate()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> IngredientCrateMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Core/Meshes/Appliances/SM_IngredientCrate.SM_IngredientCrate'"));

    if (IngredientCrateMeshAsset.Succeeded())
    {
        MeshComponent->SetStaticMesh(IngredientCrateMeshAsset.Object);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load IngredientCrate mesh!"));
    }

    AttachLocationComponent->AddLocalOffset(FVector(0.f, 0.f, -40.f));
    
    ItemsAllowed = 0;

    ApplianceName = EApplianceName::IngredientCrate;

}

void AIngredientCrate::BeginPlay()
{
    Super::BeginPlay();

    SpawnIngredients();

}

void AIngredientCrate::SpawnIngredients()
{
    for (int i = 0; i < SpawnCount; ++i)
    {
        if (AIngredient* Ingredient = GetWorld()->SpawnActorDeferred<AIngredient>(IngredientType, AttachLocationComponent->GetComponentTransform()))
        {
            Ingredient->UpdateCurrentAppliance(this);
            
            HeldItems++;

            Ingredient->FinishSpawning(Ingredient->GetTransform());
        }
    }


}
