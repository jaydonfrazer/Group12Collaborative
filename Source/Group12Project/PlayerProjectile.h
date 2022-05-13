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

	// Function that is called when the projectile hits something.
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) override;

protected:

	virtual float ProjectileSpeed() override;
	virtual float ProjectileSize() override;
	virtual int DamageAmount() override;
};
