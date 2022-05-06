// Fill out your copyright notice in the Description page of Project Settings.


#include "Group12ProjectGameModeBase.h"

void AGroup12ProjectGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	//Display debug message
	// -1 key prevents message from being updated or refreshed
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is AGroup12GameModeBase!"));
}