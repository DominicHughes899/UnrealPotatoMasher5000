// Fill out your copyright notice in the Description page of Project Settings.


#include "PotatoMasherCharacter.h"

#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
//#include "Components/WidgetComponent.h"


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
	CameraBoom->TargetArmLength = 2000.f;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 2.f;
	CameraBoom->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);
	Camera->FieldOfView = 80.f;

	// Interaction Detection Box
	InteractionDetectionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionDetectionBox"));
	InteractionDetectionBox->SetupAttachment(RootComponent);

	// Floating Hand

}

// Called when the game starts or when spawned
void APotatoMasherCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
	
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

// Called every frame
void APotatoMasherCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APotatoMasherCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &APotatoMasherCharacter::MoveForward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &APotatoMasherCharacter::MoveRight);
	}

}

