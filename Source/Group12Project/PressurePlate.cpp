// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"
#include "Components/BoxComponent.h"

// Sets default values
APressurePlate::APressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PressurePlateComponent"));
	}

	if (!BasePlate)
	{
		BasePlate = CreateDefaultSubobject<UBoxComponent>("BasePlate");
		BasePlate->BodyInstance.SetCollisionProfileName(TEXT("Trigger"));
		BasePlate->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnOverlapBegin);
		BasePlate->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::OnOverlapEnd);
		BasePlate->SetBoxExtent(FVector(50.0f, 50.0f, 10.0f));
		RootComponent = BasePlate;
	}

	// Add mesh
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
	MeshComponent->SetupAttachment(BasePlate);
}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APressurePlate::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		//Display debug message
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Plate is activated"));

		if (Door)
		{
			Door->LockAmount--;
		}
	}
}

void APressurePlate::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		//Display debug message
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Plate is deactivated"));

		if (Door)
		{
			Door->LockAmount++;
		}
	}
}