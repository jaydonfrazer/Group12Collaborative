// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "BasePickup.generated.h"

UCLASS()
class GROUP12PROJECT_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickup();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Variables")
	float Size = 30.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
	class USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* PickupMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float PickupSize();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Overlap Begins
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//Overlap Ends
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
