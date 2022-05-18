// Fill out your copyright notice in the Description page of Project Settings.


#include "KillBarrier.h"
#include "PlayerCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
AKillBarrier::AKillBarrier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create collision body
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>("BoxTrigger");
	RootComponent = BoxTrigger;

	//Set as trigger
	BoxTrigger->SetCollisionProfileName(TEXT("Trigger"));
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &AKillBarrier::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AKillBarrier::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKillBarrier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKillBarrier::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		check(GEngine != nullptr);

		//Display debug message
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Kill Barrier Touched"));

		// Find the actor that handles control for the local player.
		APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
		if (Player)
		{
			Player->Health = 0;
		}

	}
}