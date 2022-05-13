// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Variables
	Open = false;
	Lock = false;
	LockAmount = 0;

	//Create collision body
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetCollisionProfileName(TEXT("WorldStatic"));
	BoxComponent->SetBoxExtent(FVector(100.f, 5.f, 100.f));
	RootComponent = BoxComponent;

	//Create trigger body
	TriggerComponent = CreateDefaultSubobject<UBoxComponent>("TriggerComponent");
	TriggerComponent->SetCollisionProfileName(TEXT("Trigger"));
	TriggerComponent->SetBoxExtent(FVector(100.f, 50.f, 100.f));
	TriggerComponent->AttachTo(BoxComponent);
	TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnOverlapBegin);
	TriggerComponent->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnOverlapEnd);

	//Create mesh
	SpawnMesh = CreateDefaultSubobject<UStaticMeshComponent>("SpawnMesh");
	SpawnMesh->SetCollisionProfileName(TEXT("NoCollision"));
	SpawnMesh->AttachTo(BoxComponent);

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LockAmount > 0)
	{
		Lock = true;
	}
	else
	{
		Lock = false;
	}

	if (Open == true)
	{
		BoxComponent->SetCollisionProfileName(TEXT("NoCollision"));
	}
	else
	{
		BoxComponent->SetCollisionProfileName(TEXT("BlockAll"));
	}

}

void ADoor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
		if (Player)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green, TEXT("Overlap Begin"));
			if (Lock == false)
			{
				Open = true;
			}

		}
	}
}

void ADoor::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		//Display debug message
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Overlap end"));

		APlayerCharacter* Player = Cast <APlayerCharacter>(OtherActor);
		if (Player)
		{
			if (Lock == false)
			{
				Open = false;
			}
		}


	}
}