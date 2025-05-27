// Fill out your copyright notice in the Description page of Project Settings.

#include "CloudCannon.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CCProjectile.h"
#include "Engine/World.h"



// Sets default values
ACloudCannon::ACloudCannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
}

// Called when the game starts or when spawned
void ACloudCannon::BeginPlay()
{
	AActor::BeginPlay();
	
}

// Called every frame
void ACloudCannon::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);
	OnFire();
}

void ACloudCannon::OnFire()
{
	//Spawning projectile
	FVector SpawnLoc = Muzzle->GetComponentLocation();
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	GetWorld()->SpawnActor<ACCProjectile>(ProjectileClass, SpawnLoc, FRotator(0.f,0.f,0.f), ActorSpawnParams);
}


