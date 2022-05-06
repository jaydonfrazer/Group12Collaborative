// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "PlayerCharacter.h"
#include "EngineUtils.h"


AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AMyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}

void AMyPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("Attack", IE_Pressed, this, &AMyPlayerController::OnAttackPressed);
	InputComponent->BindAction("Attack", IE_Released, this, &AMyPlayerController::OnAttackReleased);
}

void AMyPlayerController::OnAttackPressed()
{

	if (APlayerCharacter* MyCharacter = Cast<APlayerCharacter>(GetPawn()))
	{
		if (MyCharacter->GetCursorToWorld())
		{

			// Debug //
			MyCharacter->Debug();
			
			//Print Clicked Location
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, FString::Printf(TEXT("Attack Location: %s"), *MyCharacter->GetCursorToWorld()->GetComponentLocation().ToString()));

		}
	}

	// Debug //
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Attack is pressed"));
}

void AMyPlayerController::OnAttackReleased()
{


	// Debug //
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Attack is released"));
}