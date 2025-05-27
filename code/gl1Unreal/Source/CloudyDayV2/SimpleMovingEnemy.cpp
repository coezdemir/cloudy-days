// Fill out your copyright notice in the Description page of Project Settings.

#include "SimpleMovingEnemy.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "MainChar.h"

ASimpleMovingEnemy::ASimpleMovingEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creating the Sphere and setting radius and relative location
	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Triggerbody"));
	InteractionSphere->SetSphereRadius(27.0f);
	FVector LocSphere = FVector(0.0f, 0.0f, 20.f);
	InteractionSphere->SetRelativeLocation(LocSphere);

	//Creating SkeletalMeshComponent(we do not assign the skeltalmesh here, because it can lead to reference breaking when packaging) and setting up attachment
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	RootComponent = SkeletalMesh;
	InteractionSphere->SetupAttachment(RootComponent);
}

void ASimpleMovingEnemy::BeginPlay() 
{
	Super::BeginPlay();
	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &ASimpleMovingEnemy::OnOverlapBegin);
}

void ASimpleMovingEnemy::Tick(float DeltaTime)
{
	AMovingActor::Tick(DeltaTime);
}

void ASimpleMovingEnemy::moveVertical(float DeltaTime)
{
	AMovingActor::moveVertical(DeltaTime);
}

void ASimpleMovingEnemy::moveHorizontal(float DeltaTime)
{
	AMovingActor::moveHorizontal(DeltaTime);
}

void ASimpleMovingEnemy::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (AMainChar* mC = Cast<AMainChar>(OtherActor)) {
		mC->takeDamage();
	}
}



