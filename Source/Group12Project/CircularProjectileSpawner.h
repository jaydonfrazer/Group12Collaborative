// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileSpawner.h"
#include "CircularProjectileSpawner.generated.h"

/**
 * 
 */
UCLASS()
class GROUP12PROJECT_API ACircularProjectileSpawner : public AProjectileSpawner
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	int ProjectileAmount;

protected:

	virtual void ShootProjectile() override;
};
