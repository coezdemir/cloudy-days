// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelLoader.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LatentActionManager.h"


// Sets default values
ALevelLoader::ALevelLoader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	//Setting up the sphere
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Triggerbody"));
	InteractionBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALevelLoader::BeginPlay()
{
	Super::BeginPlay();

	//Adding dynamic
	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &ALevelLoader::OnOverlapBegin);
}

// Called every frame
void ALevelLoader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ALevelLoader::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//Checking if the character entered the loading zone
	if (OtherActor->IsA(ACharacter::StaticClass())) {
		//Loading the level
		UGameplayStatics::OpenLevel(this, LevelToLoad, true);
	}
}