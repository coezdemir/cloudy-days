// Fill out your copyright notice in the Description page of Project Settings.

#include "WaitingMovingActor.h"


AWaitingMovingActor::AWaitingMovingActor() 
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = Mesh;
	bWaiting = true;
	Mesh->OnComponentHit.AddDynamic(this, &AWaitingMovingActor::OnComponentHit);
	Speed = 400.f;
}


void AWaitingMovingActor::Tick(float DeltaTime)
{
	if (!bWaiting) {
		AMovingActor::Tick(DeltaTime);
	}
}

void AWaitingMovingActor::OnComponentHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor->ActorHasTag(FName(TEXT("Player")))) {
		bWaiting = false;
	}
}

void AWaitingMovingActor::SetWaiting(bool Val)
{
   bWaiting = Val;
}


