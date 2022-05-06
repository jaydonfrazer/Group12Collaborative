// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "SpawnPointManager.h"
#include "SpawnPoint.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "EngineUtils.h"


// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create block body with width in mind
	SpawnBody = CreateDefaultSubobject<UBoxComponent>("SpawnBody");
	SpawnBody->SetCollisionProfileName(TEXT("Trigger"));
	SpawnBody->OnComponentBeginOverlap.AddDynamic(this, &ASpawnPoint::OnOverlapBegin);
	SpawnBody->SetBoxExtent(FVector(100.f, 100.f, 25.f));
	RootComponent = SpawnBody;

	//Create mesh
	SpawnMesh = CreateDefaultSubobject<UStaticMeshComponent>("SpawnMesh");
	SpawnMesh->SetCollisionProfileName(TEXT("NoCollision"));
	SpawnMesh->AttachTo(SpawnBody);

}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnPoint::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
		if (Player)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green, TEXT("Collision with Spawnpoint"));

			Player->SpawnPosition = GetActorLocation();
		}
	}
}
