// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovingActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "WaitingMovingActor.generated.h"

UCLASS()
class CLOUDYDAYV2_API AWaitingMovingActor : public AMovingActor
{
	GENERATED_BODY()
	
public:
	AWaitingMovingActor();
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION(BlueprintCallable)
		void SetWaiting(bool Val);
private:
		bool bWaiting;
		UBoxComponent* CollisionComp;
};
