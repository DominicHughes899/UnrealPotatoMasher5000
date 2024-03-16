// Fill out your copyright notice in the Description page of Project Settings.


#include "PotatoMasherCharacter.h"

#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
//#include "Components/WidgetComponent.h"

#include "../InteractionInterface.h"


// Sets default values
APotatoMasherCharacter::APotatoMasherCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup Components
	// Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeRotation(FRotator(-50.f, 0.f, 0.f));
	CameraBoom->TargetArmLength = 1500.f;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 2.f;
	CameraBoom->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);
	Camera->FieldOfView = 60.f;

	// Interaction Detection Box
	InteractionDetectionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionDetectionBox"));
	InteractionDetectionBox->SetupAttachment(RootComponent);
	InteractionDetectionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	InteractionDetectionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);

	// Floating Hand
	HandBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("HandBoom"));
	HandBoom->SetupAttachment(RootComponent);
	HandBoom->AddRelativeRotation(FRotator(0.f, 90.f, 0.f));
	HandBoom->AddLocalOffset(FVector(0.f, 0.f, 100.f));
	HandBoom->TargetArmLength = 50.f;
	HandBoom->bDoCollisionTest = false;
	HandBoom->bEnableCameraLag = true;
	HandBoom->CameraLagSpeed = 2.f;
	HandBoom ->bEnableCameraRotationLag = true;
	HandBoom->CameraRotationLagSpeed = 0.5f;

}

// Called when the game starts or when spawned
void APotatoMasherCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Setup input mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
	
	// Bind Overlap Functions
	OnActorBeginOverlap.AddDynamic(this, &APotatoMasherCharacter::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &APotatoMasherCharacter::OnOverlapEnd);
}

void APotatoMasherCharacter::MoveForward(const FInputActionValue& Value)
{
	if (abs(Value.Get<float>()) >= 0.1)
	{
		AddMovementInput(FVector(Value.Get<float>(), 0.f, 0.f));
	}
}

void APotatoMasherCharacter::MoveRight(const FInputActionValue& Value)
{
	if (abs(Value.Get<float>()) >= 0.1)
	{
		AddMovementInput(FVector(0.f, Value.Get<float>(), 0.f));
	}
}

void APotatoMasherCharacter::PickUpPutDown(const FInputActionValue& Value)
{
	if (HeldItem == nullptr)
	{
		PickUp();
	}
	else
	{
		PutDown();
	}
}

void APotatoMasherCharacter::Interact(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		BeginInteraction();
	}
	else
	{
		EndInteraction();
	}
}

void APotatoMasherCharacter::BeginInteraction()
{
	if (FocusedInteractable && FocusedInteractable->CanStartInteraction())
	{
		IsInteracting = true;
		CurrentFunctionDuration = FocusedInteractable->GetFunctionDuration();

		OnBeginInteraction();
	}
}

void APotatoMasherCharacter::TickInteraction(float DeltaTime)
{
	InteractionProgressTimer += DeltaTime;
	float CurrentProgress = InteractionProgressTimer / CurrentFunctionDuration;

	OnUpdateTimer(CurrentProgress);

	if (CurrentProgress >= 1.f)
	{
		TriggerInteraction(true);
	}
}

void APotatoMasherCharacter::EndInteraction()
{
	if (IsInteracting)
	{
		TriggerInteraction(false);
	}
}

void APotatoMasherCharacter::TriggerInteraction(bool Completed)
{
	InteractionProgressTimer = 0.f;
	IsInteracting = false;

	if (Completed && FocusedInteractable)
	{
		FocusedInteractable->TriggerInteraction();
	}

	if (FocusedInteractable)
	{
		FocusedInteractable->CancelInteraction();
	}

	OnEndInteraction();
}



// Called every frame
void APotatoMasherCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Focus Interactables
	if (FocusChanged())
	{
		if (FocusedInteractable)
		{
			FocusedInteractable->Focus();
		}
	}

	if (IsInteracting)
	{
		TickInteraction(DeltaTime);
	}
}

// Called to bind functionality to input
void APotatoMasherCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &APotatoMasherCharacter::MoveForward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &APotatoMasherCharacter::MoveRight);
		EnhancedInputComponent->BindAction(PickUpAction, ETriggerEvent::Started, this, &APotatoMasherCharacter::PickUpPutDown);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APotatoMasherCharacter::Interact);
	}

}

void APotatoMasherCharacter::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	IInteractionInterface* OverlappedInterface = Cast<IInteractionInterface>(OtherActor);

	if (OverlappedInterface)
	{
		InteractablesInRange.Add(OverlappedInterface);
	}
}

void APotatoMasherCharacter::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	IInteractionInterface* OverlappedInterface = Cast<IInteractionInterface>(OtherActor);

	if (OverlappedInterface && InteractablesInRange.Num() > 0)
	{
		InteractablesInRange.Remove(OverlappedInterface);
	}
}

bool APotatoMasherCharacter::FocusChanged()
{
	IInteractionInterface* ClosestInteractable = FindClosestInteractable();

	if (ClosestInteractable == FocusedInteractable)
	{
		return false;
	}
	else
	{
		if (FocusedInteractable)
		{
			FocusedInteractable->UnFocus();
		}

		FocusedInteractable = ClosestInteractable;

		return true;
	}
}

IInteractionInterface* APotatoMasherCharacter::FindClosestInteractable()
{
	int NumberOfInteractables = InteractablesInRange.Num();

	if (NumberOfInteractables == 0)
	{
		return nullptr;
	}
	else if (NumberOfInteractables == 1)
	{
		return  InteractablesInRange[0];
	}
	else
	{
		IInteractionInterface* ClosestFound = nullptr;
		float ClosestDistance = 500.f;
		FVector PlayerLocation = GetActorLocation();

		for (IInteractionInterface* InterfacePtr : InteractablesInRange)
		{
			FVector InteractableLocation = InterfacePtr->GetLocation();

			if (InteractableLocation != FVector::ZeroVector)
			{
				float DistanceToInteractable = FVector::Distance(PlayerLocation, InteractableLocation);

				if (DistanceToInteractable < ClosestDistance)
				{
					ClosestDistance = DistanceToInteractable;
					ClosestFound = InterfacePtr;
				}
			}
		}
		return ClosestFound;
	}
}

void APotatoMasherCharacter::SetCanFocusAppliance(bool NewCanFocus)
{
	if (NewCanFocus)
	{
		InteractionDetectionBox->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECollisionResponse::ECR_Overlap);
		InteractionDetectionBox->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);
	}
	else
	{
		InteractionDetectionBox->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
		InteractionDetectionBox->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
	}
}

void APotatoMasherCharacter::PickUp()
{
	if (FocusedInteractable)
	{
		if (AActor* AsActor = Cast<AActor>(FocusedInteractable))
		{
			FocusedInteractable->OnPickUp();

			IInteractionInterface* PickedUpFrom = Cast<IInteractionInterface>(FocusedInteractable->GetCurrentAppliance());
			if (PickedUpFrom)
			{
				PickedUpFrom->OnActorDetached(AsActor);
			}


			AsActor->AttachToComponent(HandBoom, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			HeldItem = AsActor;

			SetCanFocusAppliance(true);

		}
	}

}

void APotatoMasherCharacter::PutDown()
{
	if (FocusedInteractable && FocusedInteractable->CanReceiveItem(HeldItem))
	{
		if (USceneComponent* ComponentToAttachTo = FocusedInteractable->GetAttachComponent())
		{
			HeldItem->AttachToComponent(ComponentToAttachTo, FAttachmentTransformRules::SnapToTargetIncludingScale);

			IInteractionInterface* HeldItemInterface = Cast<IInteractionInterface>(HeldItem);
			if (HeldItemInterface)
			{
				HeldItemInterface->OnPutDown();
				HeldItemInterface->UpdateCurrentAppliance(Cast<AActor>(FocusedInteractable));
			}

			FocusedInteractable->OnActorAttached(HeldItem);
			
			HeldItem = nullptr;

			SetCanFocusAppliance(false);
		}
	}
}

