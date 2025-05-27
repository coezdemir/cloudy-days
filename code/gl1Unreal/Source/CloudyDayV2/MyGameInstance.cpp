// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "MySaveGame.h"
#include "Runtime/MoviePlayer/Public/MoviePlayer.h"
#include "MyGameViewportClient.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Images/SThrobber.h"

void UMyGameInstance::Init()
{
	Super::Init();
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UMyGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UMyGameInstance::EndLoadingScreen);
}

void UMyGameInstance::BeginLoadingScreen(const FString& InMapName)
{	
	//Obligatory check
	if (!IsRunningDedicatedServer())
	{
		//Creating loading screen
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
			class SLoadingScreenWidget : public SCompoundWidget
			{
			public:
				SLATE_BEGIN_ARGS(SLoadingScreenWidget) {}
				SLATE_END_ARGS()

				void Construct(const FArguments& InArgs)
			{
				ChildSlot
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Center)
						[
						SNew(SThrobber)
						.Visibility(this, &SLoadingScreenWidget::GetLoadIndicatorVisibility)
						]
						+ SVerticalBox::Slot()
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Center)
						[
						SNew(STextBlock)
						.Text(NSLOCTEXT("MoviePlayerTestLoadingScreen", "LoadingComplete", "Loading complete!"))
						.Visibility(this, &SLoadingScreenWidget::GetMessageIndicatorVisibility)
						]
					];
			}

			private:
				EVisibility GetLoadIndicatorVisibility() const
				{
					return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Collapsed : EVisibility::Visible;
				}

				EVisibility GetMessageIndicatorVisibility() const
				{
					return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Visible : EVisibility::Collapsed;
				}
			};
		//Saving level progression
		UMySaveGame* SaveGameInst = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
		const UWorld* World = GetWorld();
		if (World)SaveGameInst->LastPlayedLevel = FName(*World->GetName());
		UGameplayStatics::SaveGameToSlot(SaveGameInst, SaveGameInst->SaveSlotName, SaveGameInst->UserIndex);
		//Adding the loading screen to the viewport
		LoadingScreen.WidgetLoadingScreen = SNew(SLoadingScreenWidget);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
}

void UMyGameInstance::EndLoadingScreen(UWorld* InLoadedWorld)
{
	const UWorld* World = GetWorld();
	if (World)
	{
		UMyGameViewportClient* GameViewportClient = Cast<UMyGameViewportClient>(World->GetGameViewport());
		if (GameViewportClient)
		{
			GameViewportClient->Fade(3.f,false);
		}
	}
}
