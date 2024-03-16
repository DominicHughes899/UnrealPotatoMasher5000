// Fill out your copyright notice in the Description page of Project Settings.


#include "Appliance.h"

#include "Components/WidgetComponent.h"
#include "../UI/ApplianceInteractionPromptUI.h"
#include "GameFramework/SpringArmComponent.h"


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

	// UI
	PromptBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Prompt Boom"));
	PromptBoom->SetupAttachment(RootComponent);
	PromptBoom->SetRelativeRotation(FRotator(-70.f, 180.f, 0.f));
	PromptBoom->TargetArmLength = 200.f;
	PromptBoom->bDoCollisionTest = false;
	PromptBoom->bInheritYaw = false;

	InteractionUIComponent = CreateDefaultSubobject<UWidgetComponent>("Blueprint Interaction Prompt");
	InteractionUIComponent->SetupAttachment(PromptBoom);
	InteractionUIComponent->SetCollisionProfileName(TEXT("NoCollision"));
	InteractionUIComponent->AddRelativeRotation(FRotator(100.f, 0.f, 0.f));
	InteractionUIComponent->SetCastShadow(false);
	InteractionUIComponent->SetDrawAtDesiredSize(true);
	InteractionUIComponent->SetBlendMode(EWidgetBlendMode::Transparent);

}

// Called when the game starts or when spawned
void AAppliance::BeginPlay()
{
	Super::BeginPlay();

	// Setup UI
	if (UIClassRef)
	{
		InteractionUIComponent->SetWidgetClass(UIClassRef);

		InteractionUI = Cast<UApplianceInteractionPromptUI>(InteractionUIComponent->GetUserWidgetObject());

		if (!InteractionUI)
		{
			UE_LOG(LogTemp, Warning, TEXT("Ingredient widget not loaded sucessfully"));
		}
		else { InteractionUI->SetTitle(ApplianceName); }
	}

	
}

// Called every frame
void AAppliance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAppliance::Focus()
{
	MeshComponent->SetRenderCustomDepth(true);

	if (InteractionUI)
	{
		InteractionUI->OnPlayerFocus();
	}
}

void AAppliance::UnFocus()
{
	MeshComponent->SetRenderCustomDepth(false);

	if (InteractionUI)
	{
		InteractionUI->OnPlayerUnfocus();
	}
}

bool AAppliance::CanReceiveItem(AActor* ActorToReceive)
{
	if (HeldItems < ItemsAllowed)
	{
		return true;
	}

	// TODO: Add floating/dissapearing text displaying the reason for inability

	if (InteractionUI)
	{
		InteractionUI->AccessDenied();
	}

	return false;
}

void AAppliance::OnActorAttached(AActor* ActorAttached)
{
	HeldItems++;
}

void AAppliance::OnActorDetached(AActor* ActorDetached)
{
	HeldItems--;
}

