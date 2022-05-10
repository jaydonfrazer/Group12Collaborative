// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Group12ProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GROUP12PROJECT_API AGroup12ProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void StartPlay() override;
};
