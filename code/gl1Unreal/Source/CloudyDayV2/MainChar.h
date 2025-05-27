// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MainChar.generated.h" 

UCLASS()
class CLOUDYDAYV2_API AMainChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* Camera;

	UFUNCTION(BlueprintCallable)
		float getCurrentWater();

	UFUNCTION(BlueprintCallable)
		float getMaxWater();

	UFUNCTION(BlueprintCallable)
		void takeDamage();

	UFUNCTION(BlueprintCallable)
		void upgradeMaxWater(float Val);

	UFUNCTION(BlueprintCallable)
		void ChangeWaterLevel(float Val);

	UFUNCTION(BlueprintCallable)
		void RefillWaterCompletely();

	FTimerHandle THandle;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AActor> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AActor> ProjectileHoverClass;

	UPROPERTY(EditAnywhere, Category = "Mesh")
		class USceneComponent* Muzzle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool Hovering;

	UFUNCTION(BlueprintCallable)
		void Shoot();

private:
	void MoveForward(float Val);
	void MoveRight(float Val);
	void MyJump();
	void MoveCamUp(float Val);
	void MoveCamRight(float Val);
	void HoverPressed();
	void HoverReleased();
	void GroundPound();
	void SpawnGroundPoundCollision();
	void ChangeScale(bool Growth);
	void CalculateScaleChange();
	void MakeVincible();
	void CleanDestroy();
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	float CurrentWater;
	float MaxWater;
	float GVScale;
	bool bGrowthChange;
	bool GP;
	bool Growth;
	bool Vincible;
	FTimerHandle VincibilityHandle;
	FVector NeededScaleChange;
	FVector NormalScale;
	FVector SmallestScale;
	void Blink();
	int32 blinkcount;
	FTimerHandle BlinkHandle;
};