// Fill out your copyright notice in the Description page of Project Settings.

#include "Shockwave.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "MainChar.h"
#include "MovingActor.h"


// Sets default values
AShockwave::AShockwave() 
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	//Getting assets
	static ConstructorHelpers::FObjectFinder<UMaterialInstance>Material(TEXT("MaterialInstanceConstant'/Game/Platformer/Ocean/Materials/M_Ocean_Water_Silent_Instance.M_Ocean_Water_Silent_Instance'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>StaticMesh(TEXT("StaticMesh'/Game/Assets/Actors/Projectiles/StaticMeshes/SM_FireBlastMesh.SM_FireBlastMesh'"));
	if (StaticMesh.Succeeded() && Material.Succeeded())
	{
		Mesh->SetStaticMesh(StaticMesh.Object);
		Mesh->SetRelativeLocation(FVector(0.f, 0.f, 320.f));
		Mesh->SetMaterial(0,Material.Object);
		Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		Mesh->OnComponentBeginOverlap.AddDynamic(this, &AShockwave::OnOverlapBegin);
	}
}


// Called when the game starts or when spawned
void AShockwave::BeginPlay()
{
	AActor::BeginPlay();
	if (ChangeMaterial)Mesh->SetMaterial(0, NewMaterial);
	ScaleX = 0.1f;
	ScaleY = 0.1f;
	EnemiesAttack ? ScaleZ = 2.5f : ScaleZ = 1.25;
	Mesh->SetRelativeScale3D(FVector(ScaleX, ScaleY, ScaleZ));
}

// Called every frame
void AShockwave::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);
	float Limit;
	EnemiesAttack ? Limit = 12.5f : Limit = 2.f;
	if (GetActorScale3D().X < Limit && GetActorScale3D().Y < Limit) {
		ScaleX += 0.025f;
		ScaleY += 0.025f;
		Mesh->SetWorldScale3D(FVector(ScaleX, ScaleY, ScaleZ));
	}
	else {
		Destroy();
	}

}

void AShockwave::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!EnemiesAttack) {
		if (OtherActor->ActorHasTag(TEXT("Enemy")))OtherActor->Destroy();
	}
	else if (EnemiesAttack) {
		if (AMainChar* mC = Cast<AMainChar>(OtherActor))mC->takeDamage();
		else if (!OtherActor->ActorHasTag(TEXT("Boss")))OtherActor->Destroy();
	}
}
