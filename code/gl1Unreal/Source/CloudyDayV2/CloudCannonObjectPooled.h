// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CloudCannon.h"
#include "ObjectPool.h"
#include "CloudCannonObjectPooled.generated.h"

/**
 * 
 */
UCLASS()
class CLOUDYDAYV2_API ACloudCannonObjectPooled : public ACloudCannon
{
	GENERATED_BODY()
public:
	ACloudCannonObjectPooled();
	float GetLifeSpan();

	UPROPERTY(EditAnywhere, Category = "Spawner")
		UObjectPool* ObjectPool;

	UPROPERTY(EditAnywhere, Category = "Spawner")
		float LifeSpanofPooledObject = 30.f;

	UPROPERTY(EditAnywhere, Category = "Spawner")
		float SpawnCooldown = 3.f;

	UFUNCTION(BlueprintCallable)
		void setActivated(bool Val);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Activated;

	virtual void OnFire() override;

	FTimerHandle SpawnCooldownTimer;

	void Spawn();
protected:
	virtual void BeginPlay() override;
private:
	void Shoot();
};
