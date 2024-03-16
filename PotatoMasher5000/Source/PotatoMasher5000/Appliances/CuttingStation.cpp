// Fill out your copyright notice in the Description page of Project Settings.


#include "CuttingStation.h"

ACuttingStation::ACuttingStation()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CuttingStationMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Core/Meshes/Appliances/SM_CuttingStation.SM_CuttingStation'"));

    if (CuttingStationMeshAsset.Succeeded())
    {
        MeshComponent->SetStaticMesh(CuttingStationMeshAsset.Object);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load CuttingStation mesh!"));
    }

    FunctionDuration = 1.5f;
    ApplianceFunction = EApplianceFunctionEnum::Cut;
    ApplianceName = EApplianceName::CuttingStation;
}
