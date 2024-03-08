// Fill out your copyright notice in the Description page of Project Settings.


#include "Appliance.h"

// Sets default values
AAppliance::AAppliance()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Initialise Mesh
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);

	// Initialise AttachLocation
	AttachLocationComponent = CreateDefaultSubobject<USceneComponent>(TEXT("AttachLocation"));
	AttachLocationComponent->SetupAttachment(RootComponent);
	AttachLocationComponent->AddLocalOffset(FVector(0.f, 0.f, 100.f));

}

// Called when the game starts or when spawned
void AAppliance::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAppliance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

