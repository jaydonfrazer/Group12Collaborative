// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "PlayerProjectile.generated.h"

/**
 * 
 */
UCLASS()
class GROUP12PROJECT_API APlayerProjectile : public ABaseProjectile
{
	GENERATED_BODY()

public:
	APlayerProjectile();

protected:

	virtual float ProjectileSpeed() override;
	virtual float ProjectileSize() override;
	virtual int DamageAmount() override;
};
