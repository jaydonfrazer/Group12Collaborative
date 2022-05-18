// Fill out your copyright notice in the Description page of Project Settings.


#include "CircularProjectileSpawner.h"
#include "BaseProjectile.h"


void ACircularProjectileSpawner::ShootProjectile() 
{
	//Attempt to fire our projectile
	if (ProjectileToSpawn && IsActive)
	{
		// Get Spawner Transform
		FVector Location;
		FRotator Rotation;
		Location = GetActorLocation();
		Rotation = GetActorRotation();

		// Set Spawning offset in front of Spanwer
		SpawnOffset.Set(10.0f, 0.0f, 0.0f);

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			//Spawn the requested projectile amount
			for (int i = 0; i < ProjectileAmount; i++)
			{
				//Get the angle of which to fire each projectile at by dividing 360 by the amount of projectiles
				float RotationAngle = (360 / float(ProjectileAmount));
				Rotation += FRotator(0.f, RotationAngle, 0.f);

				// Spawn the projectile at the muzzle.
				ABaseProjectile* Projectile = World->SpawnActor<ABaseProjectile>(ProjectileToSpawn, Location, Rotation, SpawnParams);

				//Send a debug message to confirm the firing function is triggered
				//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Circular Spawner has fired!"));
			}

		}
	}
}