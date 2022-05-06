// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraTrigger.generated.h"

UCLASS()
class GROUP12PROJECT_API ACameraTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraTrigger();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Base")
	class UBoxComponent* BoxTrigger;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base")
	bool ActiveOnStart = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	AActor* Camera;
};
