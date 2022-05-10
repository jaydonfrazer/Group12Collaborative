// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "BasePawnEnemy.generated.h"

UCLASS()
class GROUP12PROJECT_API ABasePawnEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawnEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
	int Health = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
	bool isActive = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sphere collision component
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	UCapsuleComponent* CollisionComponent;

	//Projectile mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* CapsuleMeshComponent;

	//Overlap begin
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
