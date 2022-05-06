// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class GROUP12PROJECT_API AHealthPickup : public ABasePickup
{
	GENERATED_BODY()
	
public:
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
