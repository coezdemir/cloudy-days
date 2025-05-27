// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "MovingActor.generated.h"


UCLASS()
class CLOUDYDAYV2_API AMovingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	UFUNCTION(BlueprintCallable)
		virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float Speed;
	UPROPERTY(EditAnywhere, Category = "Movement")
		bool Repeat;
	//If dir==1 the actor will move towards UpLimit first
	UPROPERTY(EditAnywhere, Category = "Movement")
		int dir;

	//Vertical and horizontal are booleans to set the movement

	//If true the actor will move vertically
	UPROPERTY(EditAnywhere, Category = "Movement")
		bool Vertical;
	//If true the actor will move horizontally
	UPROPERTY(EditAnywhere, Category = "Movement")
		bool Horizontal;
	//If false actor will move on the Y-Axis
	UPROPERTY(EditAnywhere, Category = "Movement")
		bool XAxis;
	//LowLimit and UpLimit determine until which point the actor will move
	UPROPERTY(EditAnywhere, Category = "Movement")
		float UpLimit;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float LowLimit;
	UPROPERTY(EditAnywhere, Category = "Movement")
		bool ShouldWait = false;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float WaitingTime = 1.5f;
	UPROPERTY(EditAnywhere, Category = "Movement")
		bool Turn;

protected:
	UFUNCTION()
		virtual void moveVertical(float DeltaTime);
	UFUNCTION()
		virtual void moveHorizontal(float DeltaTime);
	UFUNCTION()
		void Resume();
	bool Stop;
	FTimerHandle WaitHandle;
};
