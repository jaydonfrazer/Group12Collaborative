// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingBlock.h"
#include "Components/BoxComponent.h"
#include "PlayerProjectile.h"
#include "MovingBlockComponent.h"


// Sets default values
AMovingBlock::AMovingBlock()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("MovingBlockComponent"));
	}

	SlidingAcceler = 0.2;

	if (!BaseBlock)
	{
		// Create collision body
		BaseBlock = CreateDefaultSubobject<UBoxComponent>("BaseBlock");
		BaseBlock->BodyInstance.SetCollisionProfileName(TEXT("Pawn"));
		BaseBlock->SetBoxExtent(FVector(49.5f, 49.5f, 100.0f));
		RootComponent = BaseBlock;
	}

	if (!MovementComp)
	{
		//Create instance of movement component
		MovementComp = CreateDefaultSubobject<UMovingBlockComponent>(TEXT("CustomMovementComponent"));
		MovementComp->UpdatedComponent = RootComponent;
	}

	if (!TriggerPluX)
	{
		TriggerPluX = CreateDefaultSubobject<UBoxComponent>("TriggerPluX");
		TriggerPluX->BodyInstance.SetCollisionProfileName(TEXT("Trigger"));
		TriggerPluX->SetBoxExtent(FVector(35.0f, 35.0f, 50.0f));
		TriggerPluX->SetRelativeLocation(FVector(35.0f, 0.0f, 0.0f));
		TriggerPluX->SetupAttachment(BaseBlock);

	}

	if (!TriggerPluY)
	{
		TriggerPluY = CreateDefaultSubobject<UBoxComponent>("TriggerPluY");
		TriggerPluY->BodyInstance.SetCollisionProfileName(TEXT("Trigger"));
		TriggerPluY->SetBoxExtent(FVector(35.0f, 35.0f, 50.0f));
		TriggerPluY->SetRelativeLocation(FVector(0.0f, 35.0f, 0.0f));
		TriggerPluY->SetupAttachment(BaseBlock);

	}

	if (!TriggerMinX)
	{
		TriggerMinX = CreateDefaultSubobject<UBoxComponent>("TriggerMinX");
		TriggerMinX->BodyInstance.SetCollisionProfileName(TEXT("Trigger"));
		TriggerMinX->SetBoxExtent(FVector(35.0f, 35.0f, 50.0f));
		TriggerMinX->SetRelativeLocation(FVector(-35.0f, 0.0f, 0.0f));
		TriggerMinX->SetupAttachment(BaseBlock);

	}

	if (!TriggerMinY)
	{
		TriggerMinY = CreateDefaultSubobject<UBoxComponent>("TriggerMinY");
		TriggerMinY->BodyInstance.SetCollisionProfileName(TEXT("Trigger"));
		TriggerMinY->SetBoxExtent(FVector(35.0f, 35.0f, 50.0f));
		TriggerMinY->SetRelativeLocation(FVector(0.0f, -35.0f, 0.0f));
		TriggerMinY->SetupAttachment(BaseBlock);

	}

	// Add mesh
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
	MeshComponent->SetupAttachment(BaseBlock);
}

// Called when the game starts or when spawned
void AMovingBlock::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMovingBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector SlidingSpeed(SlidingTo * SlidingAcceler);

	AddMovementInput(FVector(SlidingSpeed));


}

// Called to bind functionality to input
void AMovingBlock::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMovingBlock::TimerSet(float ShootForce, float SlideTime)
{
	//Increase acceleration from how many times player has shot movingblock, increase time as well
	SlidingAcceler += ShootForce;
	SlidingTime += SlideTime;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMovingBlock::StopFVector, 0.5f, false, SlidingTime);
}

void AMovingBlock::StopFVector()
{
	//Stop sliding and set acceleration to 0
	SlidingTo = FVector(0.f, 0.f, 0.f);
	SlidingAcceler = 0.f;
	SlidingTime = 0.f;
}