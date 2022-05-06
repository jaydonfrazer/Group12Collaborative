// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileSpawner.generated.h"

UCLASS()
class GROUP12PROJECT_API AProjectileSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileSpawner();

	UFUNCTION()
	void ShootProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float ProjectileSpawnSpeed;

	//Spawner offset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FVector SpawnOffset;

	//Spawner spawning
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<class ABaseProjectile> ProjectileToSpawn;

	//Spawner mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* ProjectileMeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float ProjectileSpawnFrequency();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FTimerHandle TimerHandle;

};
