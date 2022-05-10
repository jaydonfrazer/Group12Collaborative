// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "BasePickup.h"

// Sets default values
ABasePickup::ABasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PickupSceneComponent"));
	}
	if (!CollisionComponent)
	{
		// Use a sphere to represent collision
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// Set the sphere's collision radius
		CollisionComponent->InitSphereRadius(PickupSize());
		// Set the sphere's collision profile name to "Trigger".
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Trigger"));
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABasePickup::OnOverlapBegin);
		CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ABasePickup::OnOverlapEnd);
		//Set the root component to be collision comp
		RootComponent = CollisionComponent;
	}

	//Set Mesh Size
	float MeshSize = Size / 60.f;

	// Add mesh
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
	PickupMesh->SetCollisionProfileName(TEXT("NoCollision"));
	PickupMesh->SetRelativeScale3D(FVector(MeshSize, MeshSize, MeshSize));
	PickupMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -25.f));
	PickupMesh->SetupAttachment(CollisionComponent);
}

//Set the projectile Size
float ABasePickup::PickupSize()
{
	return Size;
}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Cyan, TEXT("Base Pickup Obtained"));

	if (OtherActor)
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
		if (Player)
		{
			Destroy();
		}
	}
}

void ABasePickup::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Cyan, TEXT("Overlap Ended"));
}