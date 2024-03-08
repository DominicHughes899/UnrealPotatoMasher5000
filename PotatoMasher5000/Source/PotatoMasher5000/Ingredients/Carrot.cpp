// Fill out your copyright notice in the Description page of Project Settings.


#include "Carrot.h"

ACarrot::ACarrot()
{
    // Load default mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CarrotMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Core/Meshes/Ingredients/SM_carrot_whole.SM_carrot_whole'"));

    if (CarrotMeshAsset.Succeeded())
    {
        UnprocessedMesh = CarrotMeshAsset.Object;
        MeshComponent->SetStaticMesh(UnprocessedMesh);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Carrot mesh!"));
    }

    // Load chopped mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CarrotChoppedMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Core/Meshes/Ingredients/SM_Carrot_Chopped.SM_Carrot_Chopped'"));

    if (CarrotChoppedMeshAsset.Succeeded())
    {
        ChoppedMesh = CarrotChoppedMeshAsset.Object;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Carrot Chopped mesh!"));
    }

    // Load diced mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CarrotDicedMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Core/Meshes/Ingredients/SM_Carrot_Diced.SM_Carrot_Diced'"));

    if (CarrotDicedMeshAsset.Succeeded())
    {
        DicedMesh = CarrotDicedMeshAsset.Object;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Carrot Diced mesh!"));
    }

}
