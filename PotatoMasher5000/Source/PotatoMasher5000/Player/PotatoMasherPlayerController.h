// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"



#include "PotatoMasherPlayerController.generated.h"


class IUserInputInterface;

/**
 * 
 */
UCLASS()
class POTATOMASHER5000_API APotatoMasherPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:

};
