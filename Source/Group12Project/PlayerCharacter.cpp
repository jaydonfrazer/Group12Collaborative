// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Components/DecalComponent.h"
#include "SpawnPointManager.h"
#include "SpawnPoint.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Containers/Array.h"
#include "PlayerCharacter.h"
#include "EngineUtils.h"
#include "Engine/SkeletalMesh.h"
#include "Components/BoxComponent.h"




// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	//Base Stats
	MaxHealth = 4;
	Health = MaxHealth;
	Lives = 2;
	MaxBullets = 3;
	Bullets = MaxBullets;
	Reloading = false;

	//Events
	OnDestroyed.AddDynamic(this, &APlayerCharacter::MyDestroyed);

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/Material/Cursor_Material.Cursor_Material'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(GEngine != nullptr);

	// Get the capsule component from our PlayerCharacter
	auto CollisionCylinder = FindComponentByClass<UCapsuleComponent>();
	CollisionCylinder->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapBegin);

	// Get the mesh component
	//auto CharacterMesh0 = FindComponentByClass<USkeletalMesh>();

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using PlayerCharacter."));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Health <= 0)
	{
		RestartPlayer();
	}

	if (Lives <= 0)
	{
		//Destroy();
	}

	//Set cursor location to player controller mouse

	if (CursorToWorld != nullptr)
	{
		if (APlayerController* PlayerCursor = Cast<APlayerController>(GetController()))
		{
			//Use a FHitResult structure to help trace a location under the cursor
			FHitResult TraceHitResult;
			PlayerCursor->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);

			//Local Variables
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();

			//Set our cursor location to what our hit result location is
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
			CursorToWorld->SetAbsolute(true, true);

			//Make player look towards cursor location
			FRotator LookAtCursor = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), TraceHitResult.Location);

			//Rotate Player towards cursor
			this->SetActorRelativeRotation(FRotator(GetActorRotation().Pitch, LookAtCursor.Yaw, GetActorRotation().Roll));
		}
	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	//Set up "Action" bindings.
	PlayerInputComponent->BindAction("Debug", IE_Pressed, this, &APlayerCharacter::Debug);

}

void APlayerCharacter::MoveForward(float Value)
{
	if (Value)
	{
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Value)
	{
		AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Value);
	}
}

void APlayerCharacter::MyDestroyed(AActor* Act)
{
	//Destroyed Event
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Player has died!"));

}

void APlayerCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		ABaseProjectile* Projectile = Cast<ABaseProjectile>(OtherActor);
		if (Projectile)
		{
			int HealthToRemove = Projectile->Damage;

			if (Projectile->HarmEnemy == false)
			{
				Health -= HealthToRemove;
				Projectile->Destroy();

				GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Projectile hit Player"));
			}
		}
		ASpawnPoint* Spawn = Cast<ASpawnPoint>(OtherActor);
		if (Spawn)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Spawn hit Player"));
		}
	}
}

void APlayerCharacter::Debug()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Debug pushed"));
	//SetActorLocation(SpawnPosition);

	// Attempt to fire a projectile.
	if (ProjectileClass && Bullets > 0)
	{

		// Get Player transform.
		FVector PlayerLocation;
		FRotator PlayerRotation;
		GetActorEyesViewPoint(PlayerLocation, PlayerRotation);

		// Set MuzzleOffset to spawn projectiles slightly in front of the Player.
		ProjectileOffset.Set(60.0f, 0.0f, 0.0f);

		// Transform ProjectileOffset from camera space to world space.
		FVector ProjectileLocation = PlayerLocation + FTransform(this->GetActorRotation()).TransformVector(ProjectileOffset);

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// Spawn the projectile at the muzzle.
			ABaseProjectile* Projectile = World->SpawnActor<ABaseProjectile>(ProjectileClass, ProjectileLocation, this->GetActorRotation(), SpawnParams);

			Bullets--;
			if (Reloading == false)
			{
				GetWorldTimerManager().SetTimer(TimerHandle, this, &APlayerCharacter::ReloadAmmo, 0.5f, false, 1.0f);
				Reloading = true;

			}

		}

	}
}

void APlayerCharacter::ReloadAmmo()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green, TEXT("Bullet Restocked!"));
	Bullets = MaxBullets;
	Reloading = false;
}

void APlayerCharacter::RestartPlayer()
{
	//Lose life
	Lives -= 1;
	Health = 4;
	SetActorLocation(SpawnPosition);

	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, FString::Printf(TEXT("Lives Remaining: %d"), Lives));
}
