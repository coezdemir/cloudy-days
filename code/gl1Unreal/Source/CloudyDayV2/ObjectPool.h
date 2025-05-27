// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CCProjectile.h"
#include "ObjectPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLOUDYDAYV2_API UObjectPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectPool();
	/*For Cem in the future, if u want to include more objects in the pool consider creating a AObjectWithinPool super class from which all objects you want to place in the pool inherit the needed methods etc.
	  If u choose to go that route replace ACCProjectile with the new super class u created*/
	ACCProjectile* GetPooledObject();
	// Called every frame
	UPROPERTY(EditAnywhere, Category = "ObjectPooler")
		TSubclassOf<class ACCProjectile> PooledObject;

	UPROPERTY(EditAnywhere, Category = "ObjectPooler")
		int PoolSize = 100;

	TArray<ACCProjectile*> Pool;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
