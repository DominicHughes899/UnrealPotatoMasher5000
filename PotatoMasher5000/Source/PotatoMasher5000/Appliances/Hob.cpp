// Fill out your copyright notice in the Description page of Project Settings.


#include "Hob.h"

AHob::AHob()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> HobMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Core/Meshes/Appliances/SM_Hob_Boil.SM_Hob_Boil'"));

    if (HobMeshAsset.Succeeded())
    {
        MeshComponent->SetStaticMesh(HobMeshAsset.Object);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Hob mesh!"));
    }

    AttachLocationComponent->AddLocalOffset(FVector(0.f, 0.f, 10.f));

    FunctionDuration = 3.f;
    ApplianceFunction = EApplianceFunctionEnum::Boil;
    ApplianceName = EApplianceName::BoilingStation;
}
