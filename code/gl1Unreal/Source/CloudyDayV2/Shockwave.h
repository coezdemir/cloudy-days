// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Classes/Materials/MaterialInstance.h"
#include "Shockwave.generated.h"

UCLASS()
class CLOUDYDAYV2_API AShockwave : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShockwave();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool ChangeMaterial;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		bool EnemiesAttack = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		UMaterialInstance* NewMaterial;
private:
	UStaticMeshComponent* Mesh;
	float ScaleX;
	float ScaleY;
	float ScaleZ;
};
