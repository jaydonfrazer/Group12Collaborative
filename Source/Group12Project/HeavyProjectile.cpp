// Fill out your copyright notice in the Description page of Project Settings.


#include "HeavyProjectile.h"

//Constructor
AHeavyProjectile::AHeavyProjectile()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set Variables
	Damage = 3;
	Speed = 150.f;
	Size = 30.f;

	//Set the sphere's collision radius
	CollisionComponent->InitSphereRadius(ProjectileSize());

	//Set Movement
	ProjectileMovementComponent->InitialSpeed = ProjectileSpeed();
	ProjectileMovementComponent->MaxSpeed = ProjectileSpeed();

	//Set Mesh Size
	float MeshSize = Size / 60.f;

	//Set Mesh
	ProjectileMeshComponent->SetRelativeScale3D(FVector(MeshSize, MeshSize, MeshSize));
	ProjectileMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -25.f));

}

void AHeavyProjectile::BeginPlay()
{
	Super::BeginPlay();

	////Debug purposes
	// 
	//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, FString::Printf(TEXT("ProjectileSpeed: %f"), ProjectileSpeed()));

}

//Set the projectile Speed
float AHeavyProjectile::ProjectileSpeed()
{
	return Speed;
}

//Set the projectile Size
float AHeavyProjectile::ProjectileSize()
{
	return Size;
}

int AHeavyProjectile::DamageAmount()
{
	return Damage;
}
