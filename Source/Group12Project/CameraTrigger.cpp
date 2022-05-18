// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraTrigger.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

// Sets default values
ACameraTrigger::ACameraTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create collision body
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>("BoxTrigger");
	RootComponent = BoxTrigger;

	//Set as trigger
	BoxTrigger->SetCollisionProfileName(TEXT("Trigger"));
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACameraTrigger::OnOverlapBegin);
	BoxTrigger->OnComponentEndOverlap.AddDynamic(this, &ACameraTrigger::OnOverlapEnd);

}

// Called when the game starts or when spawned
void ACameraTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	if (ActiveOnStart == true)
	{
		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (OurPlayerController)
		{
			if ((OurPlayerController->GetViewTarget() != Camera) && (Camera != nullptr))
			{
				//Cut instantly to camera one.
				OurPlayerController->SetViewTarget(Camera);
			}
		}
	}
}

// Called every frame
void ACameraTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACameraTrigger::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		check(GEngine != nullptr);

		//Display debug message
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, TEXT("Room Entered"));

		const float SmoothBlendTime = 0.50f;

		// Find the actor that handles control for the local player.
		APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
		if (Player)
		{
			APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
			if (OurPlayerController)
			{
				if ((OurPlayerController->GetViewTarget() != Camera) && (Camera != nullptr))
				{
					//Cut to camere.
					OurPlayerController->SetViewTargetWithBlend(Camera, SmoothBlendTime);
				}
			}

			if (ProjectileSpawn)
			{
				ProjectileSpawn->IsActive = true;
				ProjectileSpawn->ActivateShooting();
			}
			if (Enemy)
			{
				Enemy->isActive = true;
			}
		}


	}
}

void ACameraTrigger::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		//Display debug message
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, TEXT("Room Left"));

		APlayerCharacter* Player = Cast <APlayerCharacter>(OtherActor);
		if (Player)
		{

			if (ProjectileSpawn)
			{
				ProjectileSpawn->IsActive = false;
			}
			if (Enemy)
			{
				Enemy->isActive = false;
			}
		}
	}
}