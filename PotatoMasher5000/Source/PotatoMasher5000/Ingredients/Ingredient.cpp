// Fill out your copyright notice in the Description page of Project Settings.


#include "Ingredient.h"

#include "../Appliances/ApplianceFunctionEnum.h"
#include "../UI/InteractionPromptUI.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AIngredient::AIngredient()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);

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

	static ConstructorHelpers::FClassFinder <UInteractionPromptUI> PromptWidgetClass(TEXT("UserWidget'/Game/Core/UI/3D/WBP_IngredientPrompt.WBP_IngredientPrompt_C'"));

	// UserWidget'/Game/Core/UI/3D/WBP_IngredientPrompt.WBP_IngredientPrompt_C'
	


	if (PromptWidgetClass.Succeeded())
	{
		InteractionUIComponent->SetWidgetClass(PromptWidgetClass.Class);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load Ingredient Widget"));
	}

}

// Called when the game starts or when spawned
void AIngredient::BeginPlay()
{
	Super::BeginPlay();
	
	InteractionUI = Cast<UInteractionPromptUI>(InteractionUIComponent->GetUserWidgetObject());

	if (!InteractionUI)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ingredient widget not loaded sucessfully"));
	}
}

// Called every frame
void AIngredient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIngredient::Focus()
{
	MeshComponent->SetRenderCustomDepth(true);

	if (InteractionUI)
	{
		bool ShouldShowInteraction = false;
		EApplianceFunctionEnum ApplianceFunction = EApplianceFunctionEnum::None;



		if (CanInteract && CurrentApplianceInterface)
		{
			// Check Allowed Functions array
			ApplianceFunction = CurrentApplianceInterface->GetApplianceFunction();

			for (EApplianceFunctionEnum Function : AllowedFunctions)
			{
				if (ApplianceFunction == Function)
				{
					ShouldShowInteraction = true;
					break;
				}
			}
		}

		InteractionUI->OnPlayerFocus(ShouldShowInteraction, ApplianceFunction, IngredientInformation);
	}
}

void AIngredient::UnFocus()
{
	MeshComponent->SetRenderCustomDepth(false);

	if (InteractionUI)
	{
		InteractionUI->OnPlayerUnfocus();
	}
}

float AIngredient::GetFunctionDuration()
{
	if (CurrentApplianceInterface)
	{
		return CurrentApplianceInterface->GetFunctionDuration();
	}
	return 0.0f;
}

void AIngredient::OnPickUp()
{
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AIngredient::OnPutDown()
{
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

bool AIngredient::CanStartInteraction()
{
	bool ReturnValue = false;

	if ( CanInteract && CurrentApplianceInterface)
	{	
		// Check Allowed Functions array
		EApplianceFunctionEnum FunctionToCheck = CurrentApplianceInterface->GetApplianceFunction();



		for (EApplianceFunctionEnum Function : AllowedFunctions)
		{
			if (FunctionToCheck == Function)
			{
				ReturnValue = true;

				//update UI
				if (InteractionUI)
				{
					InteractionUI->OnPlayerUnfocus();
				}

				break;
			}
		}
	}

	return ReturnValue;
}

void AIngredient::CancelInteraction()
{
	Focus();
}

void AIngredient::LockInteraction()
{
	CanInteract = false;
	AllowedFunctions.Empty();
	
	if (InteractionUI)
	{
		InteractionUI->OnIngredientLocked();
	}
}

