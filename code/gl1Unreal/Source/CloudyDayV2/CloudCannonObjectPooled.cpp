// Fill out your copyright notice in the Description page of Project Settings.


#include "CloudCannonObjectPooled.h"
#include "Engine/Public/TimerManager.h"

ACloudCannonObjectPooled::ACloudCannonObjectPooled() 
{
	PrimaryActorTick.bCanEverTick = false;
	ObjectPool = CreateDefaultSubobject<UObjectPool>(TEXT("ObjectPool"));
	Activated = false;
}

void ACloudCannonObjectPooled::BeginPlay()
{
	ACloudCannon::BeginPlay();
	if(Activated)GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &ACloudCannonObjectPooled::OnFire, SpawnCooldown, false);

}

void ACloudCannonObjectPooled::setActivated(bool Val)
{
	Activated = Val;
	if(Activated)Shoot();
}

void ACloudCannonObjectPooled::OnFire()
{
	ACCProjectile* PoolableActor = ObjectPool->GetPooledObject();
	if (PoolableActor == NULL) {
		//When no object is in the pool abort
		UE_LOG(LogTemp, Warning, TEXT("Cannot spawn!"));
		if(Activated)GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &ACloudCannonObjectPooled::OnFire, SpawnCooldown, false);
		return;
	}
	//Getting the object out of the pool
	PoolableActor->SetActorLocation(Muzzle->GetComponentLocation());
	PoolableActor->SetLifeSpan(LifeSpanofPooledObject);
	PoolableActor->SetActive(true);
	UE_LOG(LogTemp, Warning, TEXT("Spawning!"));
	//Timer for despawn
	if(Activated)GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &ACloudCannonObjectPooled::OnFire, SpawnCooldown, false);
}

void ACloudCannonObjectPooled::Shoot()
{
	//Timer for ghetting object out of the pool
	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &ACloudCannonObjectPooled::OnFire, SpawnCooldown, false);
}
