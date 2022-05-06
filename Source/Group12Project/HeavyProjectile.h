// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "HeavyProjectile.generated.h"

/**
 * 
 */
UCLASS()
class GROUP12PROJECT_API AHeavyProjectile : public ABaseProjectile
{
	GENERATED_BODY()
	
public:
	AHeavyProjectile();

protected:
	virtual void BeginPlay() override;

	virtual float ProjectileSpeed() override;
	virtual float ProjectileSize() override;

	virtual int DamageAmount() override;

};
