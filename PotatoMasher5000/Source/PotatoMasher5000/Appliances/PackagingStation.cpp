// Fill out your copyright notice in the Description page of Project Settings.


#include "PackagingStation.h"
#include "GameFramework/SpringArmComponent.h"
#include "../UI/ApplianceInteractionPromptUI.h"
#include "Components/BoxComponent.h"

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

    // Proximity Detection Box
    ProximityDetectionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Proximity Detection Box"));
    ProximityDetectionBox->SetupAttachment(RootComponent);


    // =====
    ApplianceName = EApplianceName::PackagingStation;

    FIngredientStruct DicedCarrot = { EIngredientName::Carrot, EProcessedState::Diced, ECookedState::Roasted };
    FIngredientStruct ChoppedCarrot = { EIngredientName::Carrot, EProcessedState::Chopped, ECookedState::Boiled };

    OriginalRecipe.PackagedType = EPackagedType::RoastedDicedCarrots;
    OriginalRecipe.Ingredients.Add(DicedCarrot);
    OriginalRecipe.Ingredients.Add(DicedCarrot);
    OriginalRecipe.Ingredients.Add(ChoppedCarrot);
    OriginalRecipe.Ingredients.Add(ChoppedCarrot);
    OriginalRecipe.Ingredients.Add(ChoppedCarrot);


    // UI
    PromptBoom->TargetArmLength = 300.f;
}

void APackagingStation::BeginPlay()
{
    Super::BeginPlay();

    ResetActiveRecipe();

    UE_LOG(LogTemp, Warning, TEXT("Original Recipe length: %d ..... Active Recipe Length %d"), OriginalRecipe.Ingredients.Num(), ActiveRecipe.Ingredients.Num());

    //UI
    if (InteractionUI)
    {
        InteractionUI->SetRecipe();
        UpdateUI();
    }

    // Bind overlap functions
    OnActorBeginOverlap.AddDynamic(this, &APackagingStation::OnOverlapBegin);
    OnActorEndOverlap.AddDynamic(this, &APackagingStation::OnOverlapEnd);
}

void APackagingStation::OnActorAttached(AActor* ActorAttached)
{
    ActorAttached->Destroy();

    // Check Recipe Complete
    if (ActiveRecipe.Ingredients.Num() == 0)
    {
        SpawnPackagedFood();
        HeldItems++;

        ResetActiveRecipe();
    }

    UpdateUI();
}

bool APackagingStation::CanReceiveItem(AActor* ActorToReceive)
{
    if (Super::CanReceiveItem(ActorToReceive))
    {
        if (IInteractionInterface* AttachedInterface = Cast<IInteractionInterface>(ActorToReceive))
        {
            if (CheckNeededForRecipe(AttachedInterface->GetIngredientInformation()))
            {
                return true;
            }
        }
    }

    if (InteractionUI)
    {
        InteractionUI->AccessDenied();
    }

    return false;
}

void APackagingStation::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
    if (InteractionUI)
    {
        InteractionUI->OnPlayerFocus();
    }
}

void APackagingStation::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
    if (InteractionUI)
    {
        InteractionUI->OnPlayerUnfocus();
    }
}

void APackagingStation::ResetActiveRecipe()
{

    ActiveRecipe = OriginalRecipe;

}

bool APackagingStation::CheckNeededForRecipe(const FIngredientStruct& IngredientToCheck)
{
    bool IngredientFound = false;

    if (ActiveRecipe.Ingredients.Num() > 0)
    {
        int index = 0;

        for (const FIngredientStruct& Ingredient : ActiveRecipe.Ingredients)
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
            ActiveRecipe.Ingredients.RemoveAt(index);
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

void APackagingStation::UpdateUI()
{
    if (InteractionUI)
    {
        InteractionUI->ResetRecipe();
    }

    TArray<FIngredientStruct> RecipeArray = ActiveRecipe.Ingredients;
    TArray<FIngredientStruct> IngredientsChecked;

    for (const FIngredientStruct& Ingredient : RecipeArray)
    {
        int Counter = 0;

        bool AlreadyChecked = false;

        for (const FIngredientStruct& CheckedIngredient : IngredientsChecked)
        {
            if (Ingredient.Name == CheckedIngredient.Name && Ingredient.ProcessedState == CheckedIngredient.ProcessedState && Ingredient.CookedState == CheckedIngredient.CookedState)
            {
                AlreadyChecked = true;
                UE_LOG(LogTemp, Warning, TEXT("IngredientTheSame"));
            }
        }
        
        if (!AlreadyChecked)
        {

            for (const FIngredientStruct& NewIngredient : RecipeArray)
            {
                if (Ingredient.Name == NewIngredient.Name && Ingredient.ProcessedState == NewIngredient.ProcessedState && Ingredient.CookedState == NewIngredient.CookedState)
                {
                    Counter++;
                }
            }

            IngredientsChecked.Add(Ingredient);
        }

        if (Counter != 0 && InteractionUI)
        {
            InteractionUI->AppendRecipe(Counter, Ingredient);

            UE_LOG(LogTemp, Warning, TEXT("Adding"));
        }

    }

    if (InteractionUI)
    {
        InteractionUI->FinaliseRecipe();
    }
}
