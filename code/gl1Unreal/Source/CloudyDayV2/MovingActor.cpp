// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMovingActor::AMovingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Setting up default mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	Speed = 400.f;

	Stop = false;
}

// Called when the game starts or when spawned
void AMovingActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Vertical && !Stop)
	{ 
		this->moveVertical(DeltaTime); 
	}else if (Horizontal && !Stop){
		this->moveHorizontal(DeltaTime);
	}
}

void AMovingActor::moveVertical(float DeltaTime)
{	
	FVector Location = GetActorLocation();
	FVector NewLocation = Location;
	//Determining which direction the actor is going to go
	switch (dir) {
	case 1 :
		//Checking if set point is reached if the platform change direction
		if (Location.Z < UpLimit) {
			NewLocation.Z += Speed * DeltaTime;
		}else if (Location.Z >= UpLimit && Repeat) {
			dir = -1;
			if (ShouldWait) {
				Stop = true;
				GetWorldTimerManager().SetTimer(WaitHandle, this, &AMovingActor::Resume, WaitingTime, false);
			}
		}else {}
		break;
	case -1:
		//Same here
		if (Location.Z > LowLimit) {
			NewLocation.Z -= Speed * DeltaTime;
		}else if (Location.Z <= LowLimit && Repeat) {
			dir = 1;
			if (ShouldWait) {
				Stop = true;
				GetWorldTimerManager().SetTimer(WaitHandle, this, &AMovingActor::Resume, WaitingTime, false);
			}
		}else{}
		break;
	}
	SetActorLocation(NewLocation);
}

void AMovingActor::moveHorizontal(float DeltaTime)
{
	FVector Location = GetActorLocation();
	FVector NewLocation = Location;
	FRotator Rotation = GetActorRotation();
	if (XAxis) {
		switch (dir) {
		case 1:
			//The same as above is happening here just for horizontal movement on the x-axis
			if (Location.X < UpLimit) {
				NewLocation.X += Speed * DeltaTime;
			}
			else if (Location.X >= UpLimit && Repeat) {
				dir = -1;
				if (Turn) {
					Rotation.Add(0.0f, 180.0f, 0.0f);
					SetActorRotation(Rotation);
				}else if (ShouldWait) {
					Stop = true;
					GetWorldTimerManager().SetTimer(WaitHandle, this, &AMovingActor::Resume, WaitingTime, false);
				}
			}else {}
			break;
		case -1:
			if (Location.X > LowLimit) {
				NewLocation.X -= Speed * DeltaTime;
			}
			else if (Location.X <= LowLimit && Repeat) {
				dir = 1;
				if (Turn) {
					Rotation.Add(0.0f, 180.0f, 0.0f);
					SetActorRotation(Rotation);
				}else if (ShouldWait) {
					Stop = true;
					GetWorldTimerManager().SetTimer(WaitHandle, this, &AMovingActor::Resume, WaitingTime, false);
				}
			}else {}
			break;
		}
	}else {
		switch (dir) {
		case 1:
			//The same as above is happening here just for horizontal movement on the y-axis
			if (Location.Y < UpLimit) {
				NewLocation.Y += Speed * DeltaTime;
			}
			else if (Location.Y >= UpLimit && Repeat) {
				dir = -1;
				if (Turn) {
					Rotation.Add(0.0f, 180.0f, 0.0f);
					SetActorRotation(Rotation);
				} else if (ShouldWait) {
					Stop = true;
					GetWorldTimerManager().SetTimer(WaitHandle, this, &AMovingActor::Resume, WaitingTime, false);
				}
			}else {}
			break;
		case -1:
			if (Location.Y > LowLimit) {
				NewLocation.Y -= Speed * DeltaTime;
			}
			else if (Location.Y <= LowLimit && Repeat) {
				dir = 1;
				if (Turn) {
					Rotation.Add(0.0f, 180.0f, 0.0f);
					SetActorRotation(Rotation);
				}else if (ShouldWait) {
					Stop = true;
					GetWorldTimerManager().SetTimer(WaitHandle, this, &AMovingActor::Resume, WaitingTime, false);
				}
			}else {}
			break;
		}
	}
	SetActorLocation(NewLocation);
}

void AMovingActor::Resume()
{
	Stop = false;
}

