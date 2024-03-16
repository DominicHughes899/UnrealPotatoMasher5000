// Fill out your copyright notice in the Description page of Project Settings.


#include "Counter.h"

ACounter::ACounter()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CounterMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Core/Meshes/Appliances/SM_Counter_Base.SM_Counter_Base'"));

    if (CounterMeshAsset.Succeeded())
    {
        MeshComponent->SetStaticMesh(CounterMeshAsset.Object);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Counter mesh!"));
    }
}
