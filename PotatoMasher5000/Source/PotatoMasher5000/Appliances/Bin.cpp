// Fill out your copyright notice in the Description page of Project Settings.


#include "Bin.h"

ABin::ABin()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> BinMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Core/Meshes/Appliances/SM_Bin.SM_Bin'"));

    if (BinMeshAsset.Succeeded())
    {
        MeshComponent->SetStaticMesh(BinMeshAsset.Object);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Bin mesh!"));
    }

    ApplianceName = EApplianceName::Bin;
}

