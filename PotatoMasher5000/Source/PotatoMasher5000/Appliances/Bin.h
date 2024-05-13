// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Appliance.h"
#include "Bin.generated.h"

/**
 * 
 */
UCLASS()
class POTATOMASHER5000_API ABin : public AAppliance
{
	GENERATED_BODY()
	
public:
	ABin();

	void OnActorAttached(AActor* ActorAttached) override { ActorAttached->Destroy(); }
};
