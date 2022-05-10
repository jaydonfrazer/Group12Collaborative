// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GROUP12PROJECT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();

protected:

	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	//Input handlers
	void OnAttackPressed();
	void OnAttackReleased();
};
