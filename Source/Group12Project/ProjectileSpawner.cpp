// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileSpawner.h"
#include "BaseProjectile.h"

// Sets default values
AProjectileSpawner::AProjectileSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add mesh
	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
	ProjectileMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
	ProjectileMeshComponent->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));
	ProjectileMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -12.5f));
	RootComponent = ProjectileMeshComponent;

	IsActive = false;

}

//Set how frequently the projectiles spawn
float AProjectileSpawner::ProjectileSpawnFrequency()
{
	return ProjectileSpawnSpeed;
}

// Called when the game starts or when spawned
void AProjectileSpawner::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AProjectileSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileSpawner::ActivateShooting()
{
	// Call a timer function to trigger from overlap
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AProjectileSpawner::ShootProjectile, ProjectileSpawnFrequency(), true, 0.0f);
}

void AProjectileSpawner::ShootProjectile()
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

			// Spawn the projectile at the muzzle.
			ABaseProjectile* Projectile = World->SpawnActor<ABaseProjectile>(ProjectileToSpawn, Location, Rotation, SpawnParams);

			//Send a debug message to confirm the firing function is triggered
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Spawner has fired!"));

		}
	}
}
