// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingBlock.h"
#include "PlayerProjectile.h"
#include "MovingBlockComponent.h"

//Constructor
APlayerProjectile::APlayerProjectile()
{
	//Set Variables
	Damage = 3;
	Speed = 800.f;
	Size = 20.f;
	HarmEnemy = true;

	//Set the sphere's collision radius
	CollisionComponent->InitSphereRadius(ProjectileSize());

	//Set Movement
	ProjectileMovementComponent->InitialSpeed = ProjectileSpeed();
	ProjectileMovementComponent->MaxSpeed = ProjectileSpeed();
}

//Set the projectile Speed
float APlayerProjectile::ProjectileSpeed()
{
	return Speed;
}

//Set the projectile Size
float APlayerProjectile::ProjectileSize()
{
	return Size;
}

int APlayerProjectile::DamageAmount()
{
	return Damage;
}

void APlayerProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}
	AMovingBlock* MovingBlock = Cast<AMovingBlock>(OtherActor);
	if (MovingBlock && OtherComponent)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Projectile Hit: %s"), *OtherComponent->GetName()));

		if (OtherComponent->GetName() == "TriggerPluX")
		{
			MovingBlock->SlidingTo = FVector(-1.0f, 0.0f, 0.0f);
		}
		else if (OtherComponent->GetName() == "TriggerPluY")
		{
			MovingBlock->SlidingTo = FVector(0.0f, -1.0f, 0.0f);
		}
		else if (OtherComponent->GetName() == "TriggerMinX")
		{
			MovingBlock->SlidingTo = FVector(1.0f, 0.0f, 0.0f);
		}
		else if (OtherComponent->GetName() == "TriggerMinY")
		{
			MovingBlock->SlidingTo = FVector(0.0f, 1.0f, 0.0f);
		}

		MovingBlock->TimerSet(0.4f, 0.5f);
	}

	Destroy();
}