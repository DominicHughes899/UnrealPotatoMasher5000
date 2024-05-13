// Fill out your copyright notice in the Description page of Project Settings.


#include "PackagedFood.h"

APackagedFood::APackagedFood()
{
    // Load default mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> PackagedMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Core/Meshes/Ingredients/SM_PackagedFood.SM_PackagedFood'"));

    if (PackagedMeshAsset.Succeeded())
    {
        MeshComponent->SetStaticMesh(PackagedMeshAsset.Object);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Packaged mesh!"));
    }
}
