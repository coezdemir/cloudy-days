// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCharController.h"
#include "Blueprint/UserWidget.h"
#include "Components/InputComponent.h"



void AMainCharController::BeginPlay()
{
	Super::BeginPlay();

	if (wWaterBar) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget and store it.
		WaterBar = CreateWidget<UUserWidget>(this, wWaterBar);

		// now you can use the widget directly since you have a referance for it.
		// Extra check to  make sure the pointer holds the widget.
		if (WaterBar)
		{
			//let add it to the view port
			WaterBar->AddToViewport();
		}
	}

}

void AMainCharController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Pause",IE_Pressed ,this, &AMainCharController::CreateESCMenueWidget);
}

void AMainCharController::CreateESCMenueWidget()
{
	if (wESCMenu) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget and store it.
		ESCMenu = CreateWidget<UUserWidget>(this, wESCMenu);

		// now you can use the widget directly since you have a referance for it.
		// Extra check to  make sure the pointer holds the widget.
		if (ESCMenu)
		{
			//let add it to the view port
			ESCMenu->AddToViewport();
			this->SetPause(true);
			this->SetInputMode(FInputModeUIOnly());
			this->bShowMouseCursor = true;
			this->bEnableClickEvents = true;
			this->bEnableMouseOverEvents = true;
		}
	}
}



