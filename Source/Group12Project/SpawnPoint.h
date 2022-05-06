// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

UCLASS()
class GROUP12PROJECT_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPoint();

	//Set actor box component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base")
	class UBoxComponent* SpawnBody;

	//Set actor mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base")
	class UStaticMeshComponent* SpawnMesh;

	//Add overlap function
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
