// Fill out your copyright notice in the Description page of Project Settings.


#include "PackagingStation.h"
#include "GameFramework/SpringArmComponent.h"
#include "../UI/ApplianceInteractionPromptUI.h"

#include "../Ingredients/PackagedFood.h"

APackagingStation::APackagingStation()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> PackagingStationMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Core/Meshes/Appliances/SM_PackagingStation.SM_PackagingStation'"));

    if (PackagingStationMeshAsset.Succeeded())
    {
        MeshComponent->SetStaticMesh(PackagingStationMeshAsset.Object);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load PackagingStation mesh!"));
    }

    AttachLocationComponent->AddLocalOffset(FVector(-10.f, 0.f, 0.f));

    ApplianceName = EApplianceName::PackagingStation;

    FIngredientStruct DicedCarrot = { EIngredientName::Carrot, EProcessedState::Unprocessed, ECookedState::Raw };

    OriginalRecipe.Add(DicedCarrot);
    OriginalRecipe.Add(DicedCarrot);


    // UI
    PromptBoom->TargetArmLength = 300.f;
}

void APackagingStation::BeginPlay()
{
    Super::BeginPlay();

    ResetActiveRecipe();

    UE_LOG(LogTemp, Warning, TEXT("Original Recipe length: %d ..... Active Recipe Length %d"), OriginalRecipe.Num(), ActiveRecipe.Num());

    //UI
    if (InteractionUI)
    {
        InteractionUI->SetRecipe();
    }
}

void APackagingStation::OnActorAttached(AActor* ActorAttached)
{
    ActorAttached->Destroy();

    // Check Recipe Complete
    if (ActiveRecipe.Num() == 0)
    {
        SpawnPackagedFood();
        HeldItems++;

        ResetActiveRecipe();
    }
}

bool APackagingStation::CanReceiveItem(AActor* ActorToReceive)
{
    if (Super::CanReceiveItem(ActorToReceive))
    {
        if (IInteractionInterface* AttachedInterface = Cast<IInteractionInterface>(ActorToReceive))
        {
            if (CheckNeededForRecipe(AttachedInterface->GetIngredientInformation()))
            {
                UE_LOG(LogTemp, Warning, TEXT("True: %d"), ActiveRecipe.Num());

                return true;
            }
        }


    }
    UE_LOG(LogTemp, Warning, TEXT("False: %d"), ActiveRecipe.Num());

    return false;
}

void APackagingStation::ResetActiveRecipe()
{

    ActiveRecipe = OriginalRecipe;

}

bool APackagingStation::CheckNeededForRecipe(const FIngredientStruct& IngredientToCheck)
{
    bool IngredientFound = false;

    if (ActiveRecipe.Num() > 0)
    {
        int index = 0;

        for (const FIngredientStruct& Ingredient : ActiveRecipe)
        {
            if (Ingredient.Name == IngredientToCheck.Name &&
                Ingredient.ProcessedState == IngredientToCheck.ProcessedState &&
                Ingredient.CookedState == IngredientToCheck.CookedState)
            {
                IngredientFound = true;
                break;
            }

            index++;
        }

        if (IngredientFound)
        {
            ActiveRecipe.RemoveAt(index);
            return true;
        }
    }

    return false;
}

void APackagingStation::SpawnPackagedFood()
{
    APackagedFood* SpawnedPackage = GetWorld()->SpawnActorDeferred<APackagedFood>(APackagedFood::StaticClass(), GetTransform());

    if (SpawnedPackage)
    {
        SpawnedPackage->SetPackagedType(EPackagedType::RoastedDicedCarrots);
        SpawnedPackage->UpdateCurrentAppliance(this);
        SpawnedPackage->FinishSpawning(GetTransform());
        SpawnedPackage->AttachToComponent(GetAttachComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
    }
}
