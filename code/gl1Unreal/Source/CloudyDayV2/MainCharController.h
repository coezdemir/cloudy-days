// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "MainCharController.generated.h"

/**
 * 
 */
UCLASS()
class CLOUDYDAYV2_API AMainCharController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Reference UMG asset in the editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> wWaterBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> wESCMenu;

	// Variables to hold the widgets
	UUserWidget* WaterBar;
	UUserWidget* ESCMenu;
	
	virtual void BeginPlay() override;

protected:
	virtual void SetupInputComponent() override;

private:
	void CreateESCMenueWidget();
};
