// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool.h"
#include "GameFramework/Actor.h"
#include "Engine.h"


// Sets default values for this component's properties
UObjectPool::UObjectPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}


ACCProjectile * UObjectPool::GetPooledObject(){
	for (ACCProjectile* PoolableActor : Pool) {
		if (!PoolableActor->IsActive()) {
			return PoolableActor;
		}
	}
	return nullptr;
}

// Called when the game starts
void UObjectPool::BeginPlay()
{
	Super::BeginPlay();
	if (PooledObject != NULL)
	{	
		UWorld* const World = GetWorld();
		if (World) {
			for (int i = 0; i < PoolSize; i++){
				ACCProjectile* PoolableActor = World->SpawnActor<ACCProjectile>(PooledObject, FVector().ZeroVector, FRotator().ZeroRotator);
				PoolableActor->SetActive(false);
				Pool.Add(PoolableActor);
			}
		}
	}
}


