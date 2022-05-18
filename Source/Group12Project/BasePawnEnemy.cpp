// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawnEnemy.h"
#include "Components/CapsuleComponent.h"
#include "BaseProjectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
ABasePawnEnemy::ABasePawnEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("EnemySceneComponent"));
	}
	if (!CollisionComponent)
	{
		// Use a capsule to represent collision
		CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
		// Set collision to Pawn
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Pawn"));
		// Event called when component hits something.
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABasePawnEnemy::OnOverlapBegin);;
		//Set the root component to be collision comp
		RootComponent = CollisionComponent;
	}

	// Add mesh
	CapsuleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CapsuleMeshComponent"));
	CapsuleMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
	CapsuleMeshComponent->SetupAttachment(CollisionComponent);
}

//Set how frequently the blocks spawn
float ABasePawnEnemy::ProjectileSpawnFrequency()
{
	return ProjectileSpawnSpeed;
}

// Called when the game starts or when spawned
void ABasePawnEnemy::BeginPlay()
{
	Super::BeginPlay();

	//get player from the world once game starts and cast towards them
	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABasePawnEnemy::ShootProjectile, ProjectileSpawnFrequency(), true, 0.0f);

	
}

// Called every frame
void ABasePawnEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Health <= 0)
	{
		if (Door)
		{
			Door->LockAmount--;
		}
		Destroy();
	}
	if (isActive == true)
	{
		//Make Enemy look towards Player location
		FRotator LookAtPlayer = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Player->GetActorLocation());

		//Rotate towards Player
		this->SetActorRelativeRotation(FRotator(GetActorRotation().Pitch, LookAtPlayer.Yaw, GetActorRotation().Roll));
	}
}

void ABasePawnEnemy::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Projectile hit Enemy"));

		ABaseProjectile* Projectile = Cast<ABaseProjectile>(OtherActor);
		if (Projectile && isActive == true)
		{
			int HealthToRemove = Projectile->Damage;

			if (Projectile->HarmEnemy == true)
			{
				Health -= HealthToRemove;
				Projectile->Destroy();

				GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Projectile hit Enemy"));
			}
		}
	}
}

void ABasePawnEnemy::ShootProjectile()
{
	//Attempt to fire our projectile
	if (ProjectileToSpawn && isActive)
	{
		// Get Player transform.
		FVector EnemyLocation;
		FRotator EnemyRotation;
		GetActorEyesViewPoint(EnemyLocation, EnemyRotation);

		// Set MuzzleOffset to spawn projectiles slightly in front of the Player.
		ProjectileOffset.Set(60.0f, 0.0f, 0.0f);

		// Transform ProjectileOffset from camera space to world space.
		FVector ProjectileLocation = EnemyLocation + FTransform(this->GetActorRotation()).TransformVector(ProjectileOffset);

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// Spawn the projectile at the muzzle.
			ABaseProjectile* Projectile = World->SpawnActor<ABaseProjectile>(ProjectileToSpawn, ProjectileLocation, this->GetActorRotation(), SpawnParams);
		}
	}
}