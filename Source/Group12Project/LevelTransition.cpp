// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTransition.h"
#include "PlayerCharacter.h"
#include "Components/BoxComponent.h"


// Sets default values
ALevelTransition::ALevelTransition()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create collision body
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>("BoxTrigger");
	RootComponent = BoxTrigger;

	//Set as trigger
	BoxTrigger->SetCollisionProfileName(TEXT("Trigger"));
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ALevelTransition::OnOverlapBegin);

	//Set up TArray with our levels
	Levels.Add("MainMenu"); // Map 0
	Levels.Add("Level01"); // Map 1
	Levels.Add("Level02"); // Map 2
	Levels.Add("LevelBOSS"); // Map 3
}

// Called when the game starts or when spawned
void ALevelTransition::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelTransition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelTransition::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		check(GEngine != nullptr);

		//Display debug message
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, TEXT("Transition Activated"));

		// Find the actor that handles control for the local player.
		APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
		if (Player)
		{
			//Get our current map name
			FString Current = GetWorld()->GetMapName();
			Current.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

			//We have the current map name now
			for (int i = 0; i < Levels.Num(); i++)
			{
				//As were iterating through the levels, check which index our level name matches currently
				if (Current == Levels[i])
				{
					//If current level matches a point in the array, then go to the next level

					if (i == Levels.Num() - 1)
					{
						//If level is the last one in the order, go back to the main menu
						i = -1;
					}

					//Open level
					UGameplayStatics::OpenLevel(GetWorld(), FName(Levels[i + 1]));
					break;

				}
			}
		}

	}
}