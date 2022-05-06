// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BaseProjectile.generated.h"

UCLASS()
class GROUP12PROJECT_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
	int Damage = 2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Variables")
	float Speed = 300.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Variables")
	float Size = 15.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Variables")
	bool HarmEnemy = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// These are virtual variables we want to override in the child classes
	virtual float ProjectileSpeed();
	virtual float ProjectileSize();

	virtual int DamageAmount();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sphere collision component
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	USphereComponent* CollisionComponent;

	// Projectile movement component
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	UProjectileMovementComponent* ProjectileMovementComponent;

	//Projectile mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* ProjectileMeshComponent;

	// Function that is called when the projectile hits something.
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
