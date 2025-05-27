// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "MovingActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Materials/MaterialInstance.h"
#include "FrozenMovingCloud.generated.h"

/**
 * 
 */
UCLASS()
class CLOUDYDAYV2_API AFrozenMovingCloud : public AMovingActor
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	AFrozenMovingCloud();
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* TriggerBody;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		AActor* CollidingActor;
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	bool Enemies;
private:
	bool Frozen;
	void unFreeze();
	void moveVertical(float DeltaTime) override;
	void moveHorizontal(float DeltaTime) override;
	UMaterialInstance*  Un = nullptr;
};
