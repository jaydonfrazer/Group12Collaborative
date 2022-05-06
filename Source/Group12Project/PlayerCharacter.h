// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpawnPointManager.h"
#include "SpawnPoint.h"
#include "BaseProjectile.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class GROUP12PROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	FVector SpawnPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStats")
	int Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStats")
	int Lives;

	//Decal that projects to the cursor location
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cursor")
	class UDecalComponent* CursorToWorld;
	//Returns CursorToWorld as a subobject
	FORCEINLINE class UDecalComponent* GetCursorToWorld() {return CursorToWorld;}

	// Projectile muzzle offset from the player location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector ProjectileOffset;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ABaseProjectile> ProjectileClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handles input for moving forward and backward.
	UFUNCTION()
	void MoveForward(float Value);

	//Handles input for moving right and left.
	UFUNCTION()
	void MoveRight(float Value);

	//Input for debug
	UFUNCTION()
	void Debug();

	//Set location of the player at their last overlapped checkpoint
	UFUNCTION()
	void RestartPlayer();

	UFUNCTION()
	void MyDestroyed(AActor* Act);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

};
