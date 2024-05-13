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

    // Add To allowed functions
    AllowedFunctions.Add(EApplianceFunctionEnum::Cut);
    AllowedFunctions.Add(EApplianceFunctionEnum::Roast);
    AllowedFunctions.Add(EApplianceFunctionEnum::Boil);

    // Set default ingredient information
    IngredientInformation.Name = EIngredientName::Carrot;
}

void ACarrot::TriggerInteraction()
{
    if (CurrentApplianceInterface)
    {
        EApplianceFunctionEnum ApplianceFunction = CurrentApplianceInterface->GetApplianceFunction();

        if (ApplianceFunction == EApplianceFunctionEnum::Cut)
        {
            Interaction_Cut();
        }
        else if (ApplianceFunction == EApplianceFunctionEnum::Roast)
        {
            Interaction_Roast();
        }
        else if (ApplianceFunction == EApplianceFunctionEnum::Boil)
        {
            Interaction_Boil();
        }
    }
}

void ACarrot::Interaction_Cut()
{
    EProcessedState& ProcessedState = IngredientInformation.ProcessedState;

    if (ProcessedState == EProcessedState::Unprocessed)
    {
        ProcessedState = EProcessedState::Chopped;
        MeshComponent->SetStaticMesh(ChoppedMesh);
    }
    else if (ProcessedState == EProcessedState::Chopped)
    {
        ProcessedState = EProcessedState::Diced;
        MeshComponent->SetStaticMesh(DicedMesh);

        AllowedFunctions.Remove(EApplianceFunctionEnum::Cut);
    }
}

void ACarrot::Interaction_Roast()
{
    ECookedState& CookedState = IngredientInformation.CookedState;

    if (CookedState == ECookedState::Raw)
    {
        CookedState = ECookedState::Roasted;

        LockInteraction();
    }
}

void ACarrot::Interaction_Boil()
{
    ECookedState& CookedState = IngredientInformation.CookedState;

    if (CookedState == ECookedState::Raw)
    {
        CookedState = ECookedState::Boiled;

        LockInteraction();
    }
}
