// Fill out your copyright notice in the Description page of Project Settings.

#include "FrozenMovingCloud.h"
#include "Shockwave.h"
#include "ConstructorHelpers.h"

AFrozenMovingCloud::AFrozenMovingCloud()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = Mesh;
	static ConstructorHelpers::FObjectFinder<UMaterialInstance>Material(TEXT("MaterialInstanceConstant'/Game/Platformer/Materials/M_Cloud_Still_Inst.M_Cloud_Still_Inst'"));
	if (Material.Succeeded() && Material.Object != NULL)Un = Material.Object;
	TriggerBody = CreateDefaultSubobject<UBoxComponent>(TEXT("Triggerbody"));
	TriggerBody->SetupAttachment(Mesh);
	Speed = 400.f;
	Frozen = true;
}

void AFrozenMovingCloud::BeginPlay()
{
	Super::BeginPlay();
	TriggerBody->OnComponentBeginOverlap.AddDynamic(this, &AFrozenMovingCloud::OnOverlapBegin);

}

void AFrozenMovingCloud::Tick(float DeltaTime)
{
	if (!Frozen) {
		AMovingActor::Tick(DeltaTime);
	}
	else {}
}

void AFrozenMovingCloud::moveVertical(float DeltaTime)
{
	AMovingActor::moveVertical(DeltaTime);
}

void AFrozenMovingCloud::moveHorizontal(float DeltaTime)
{
	AMovingActor::moveHorizontal(DeltaTime);
}

void AFrozenMovingCloud::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//TODO Check if all enemies are defeated
	if (Enemies) {}
	else {
		if (OtherActor->IsA(AShockwave::StaticClass()))
		{
			Frozen = false;
			Mesh->SetMaterial(0, Un);
		}
	}
}
