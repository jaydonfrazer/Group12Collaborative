// Fill out your copyright notice in the Description page of Project Settings.


#include "LightProjectile.h"

//Constructor
ALightProjectile::ALightProjectile()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set Variables
	Damage = 1;
	Speed = 600.f;
	Size = 7.5f;

	//Set the sphere's collision radius
	CollisionComponent->InitSphereRadius(ProjectileSize());

	//Set Movement
	ProjectileMovementComponent->InitialSpeed = ProjectileSpeed();
	ProjectileMovementComponent->MaxSpeed = ProjectileSpeed();

	//Set Mesh Size
	float MeshSize = Size / 60.f;

	//Set Mesh
	ProjectileMeshComponent->SetRelativeScale3D(FVector(MeshSize, MeshSize, MeshSize));
	ProjectileMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -6.25f));

}

void ALightProjectile::BeginPlay()
{
	Super::BeginPlay();

	////Debug purposes
	// 
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, FString::Printf(TEXT("ProjectileSpeed: %f"), ProjectileSpeed()));

}

//Set the projectile Speed
float ALightProjectile::ProjectileSpeed()
{
	return Speed;
}

//Set the projectile Size
float ALightProjectile::ProjectileSize()
{
	return Size;
}

int ALightProjectile::DamageAmount()
{
	return Damage;
}