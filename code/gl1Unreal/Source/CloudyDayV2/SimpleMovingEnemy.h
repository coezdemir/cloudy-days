// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovingActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "SimpleMovingEnemy.generated.h"

/**
 * 
 */
UCLASS()
class CLOUDYDAYV2_API ASimpleMovingEnemy : public AMovingActor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//Sets default values for this actor's properties
	ASimpleMovingEnemy();

	//Called every frame
	virtual void Tick(float DeltaTime) override;
	void moveVertical(float DeltaTime) override;
	void moveHorizontal(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, Category = SkeletalMesh)
		class USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USphereComponent* InteractionSphere;
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};