// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPointManager.h"
//Helps find all the spawnpoints automatically rather than manually
#include "EngineUtils.h"

// Sets default values
ASpawnPointManager::ASpawnPointManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnPointManager::BeginPlay()
{
	Super::BeginPlay();
	
	//Gets UWorld pointer as parameter
	UWorld* world = GetWorld();

	//Search for class of actor we are searching for
	for (TActorIterator<ASpawnPoint> Iterator(world, ASpawnPoint::StaticClass()); Iterator; ++Iterator)
	{
		ASpawnPoint* FoundActor = *Iterator;
		//Check if item is not NULL and is accessible, then add it to our array
		if (FoundActor != NULL)
			Spawns.Add(FoundActor);
	}

	ResetCheckPoints();
}

// Called every frame
void ASpawnPointManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnPointManager::ResetCheckPoints()
{
	//Check if no spawns are present in the current level
	int32 countSpawns = Spawns.Num();
	if (countSpawns == 0)
		return;

	//Get the spawnpoint we want
	ASpawnPoint* spawn = Spawns[1];
	spawn->Destroy();
}