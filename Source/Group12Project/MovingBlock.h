// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MovingBlock.generated.h"

UCLASS()
class GROUP12PROJECT_API AMovingBlock : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMovingBlock();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base")
	class UBoxComponent* BaseBlock;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base")
	class UBoxComponent* TriggerPluX;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base")
	class UBoxComponent* TriggerPluY;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base")
	class UBoxComponent* TriggerMinX;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base")
	class UBoxComponent* TriggerMinY;

	//Mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStats")
	FVector SlidingTo = FVector(0.f, 0.f, 0.f);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	class UMovingBlockComponent* MovementComp;

};
