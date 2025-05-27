// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CloudCannon.generated.h"

UCLASS()
class CLOUDYDAYV2_API ACloudCannon : public AActor
{
	GENERATED_BODY()
	
public:	
	ACloudCannon();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ACCProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Mesh")
		class USceneComponent* Muzzle;

	UFUNCTION(BlueprintCallable)
		virtual void OnFire();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
