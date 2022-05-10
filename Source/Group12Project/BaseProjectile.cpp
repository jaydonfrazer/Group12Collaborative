// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "BaseProjectile.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if (!CollisionComponent)
	{
		// Use a sphere to represent collision
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// Set the sphere's collision radius
		CollisionComponent->InitSphereRadius(ProjectileSize());
		// Set the sphere's collision profile name to "Projectile".
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
		// Event called when component hits something.
		CollisionComponent->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHit);
		//Set the root component to be collision comp
		RootComponent = CollisionComponent;
	}

	if (!ProjectileMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = ProjectileSpeed();
		ProjectileMovementComponent->MaxSpeed = ProjectileSpeed();
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	//Set Mesh Size
	float MeshSize = Size / 60.f;

	// Add mesh
	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
	ProjectileMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
	ProjectileMeshComponent->SetRelativeScale3D(FVector(MeshSize, MeshSize, MeshSize));
	ProjectileMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -12.5f));
	ProjectileMeshComponent->SetupAttachment(CollisionComponent);

	// Delete the projectile after 10 seconds.
	InitialLifeSpan = 10.0f;
}

//Set the projectile Speed
float ABaseProjectile::ProjectileSpeed()
{
	return Speed;
}

//Set the projectile Size
float ABaseProjectile::ProjectileSize()
{
	return Size;
}

//Set damage of projectile
int ABaseProjectile::DamageAmount()
{
	return Damage;
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	//Damage = DamageAmount();

	////Send a debug message to confirm the firing function is triggered
	// 
	//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Projectile Spawned!"));
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function that is called when the projectile hits something.
void ABaseProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);

	}

	Destroy();
}
