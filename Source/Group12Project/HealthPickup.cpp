// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "HealthPickup.h"

void AHealthPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Cyan, TEXT("Health Pickup Obtained"));

	if (OtherActor)
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
		if (Player && Player->Health<4)
		{
			Player->Health += 1;
			Destroy();
		}
	}
}
