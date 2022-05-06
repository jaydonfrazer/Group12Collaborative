// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerProjectile.h"

//Constructor
APlayerProjectile::APlayerProjectile()
{
	//Set Variables
	Damage = 3;
	Speed = 600.f;
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