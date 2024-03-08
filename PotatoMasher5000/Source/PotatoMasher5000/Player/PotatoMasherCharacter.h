// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "InputActionValue.h"

#include "PotatoMasherCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;

class IInteractionInterface;


UCLASS()
class POTATOMASHER5000_API APotatoMasherCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APotatoMasherCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ==== Input Handler ====
	// Set in BP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveRightAction;

	void MoveForward(const FInputActionValue& Value);

	void MoveRight(const FInputActionValue& Value);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:


	// ==== Components ====
	// Camera
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;
	

	// Interaction Detection Box
	UPROPERTY(EditAnywhere)
	UBoxComponent* InteractionDetectionBox;

	// Floating Hand
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* HandBoom;

	// ==== Interaction ====
	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);

	bool FocusChanged();
	IInteractionInterface* FindClosestInteractable();

	TArray<IInteractionInterface*> InteractablesInRange;
	IInteractionInterface* FocusedInteractable;
};
