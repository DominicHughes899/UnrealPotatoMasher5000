// Fill out your copyright notice in the Description page of Project Settings.


#include "Oven.h"

AOven::AOven()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> OvenMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Core/Meshes/Appliances/SM_Oven.SM_Oven'"));

    if (OvenMeshAsset.Succeeded())
    {
        MeshComponent->SetStaticMesh(OvenMeshAsset.Object);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Oven mesh!"));
    }

    AttachLocationComponent->AddLocalOffset(FVector(0.f, 0.f, -50.f));

    FunctionDuration = 3.f;
    ApplianceFunction = EApplianceFunctionEnum::Roast;

    ApplianceName = EApplianceName::OvenStation;
}
