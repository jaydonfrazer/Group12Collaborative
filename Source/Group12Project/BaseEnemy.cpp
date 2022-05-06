// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "Components/CapsuleComponent.h"
#include "BaseProjectile.h"


// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("EnemySceneComponent"));
	}
	if (!CollisionComponent)
	{
		// Use a capsule to represent collision
		CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
		// Set the capsule's collision profile name to "Actor".
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Pawn"));
		// Event called when component hits something.
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseEnemy::OnOverlapBegin);;
		//Set the root component to be collision comp
		RootComponent = CollisionComponent;
	}

	// Add mesh
	CapsuleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CapsuleMeshComponent"));
	CapsuleMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
	CapsuleMeshComponent->SetupAttachment(CollisionComponent);

}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Health == 0)
	{
		Destroy();
	}

}

void ABaseEnemy::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Projectile hit Enemy"));

		ABaseProjectile* Projectile = Cast<ABaseProjectile>(OtherActor);
		if (Projectile)
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