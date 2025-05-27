// Copyright 2015 Moritz Wundke. All Rights Reserved.
// Released under MIT

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "MyGameViewportClient.generated.h"


UCLASS()
class CLOUDYDAYV2_API UMyGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
	
public:

	
	virtual void PostRender(UCanvas* Canvas) override;

	//Clear fading state
	virtual void ClearFade();

	//Used for Fade to and from black
	virtual void Fade(const float Duration, const bool bToBlack);
	

	/** Does the actual screen fading */
	void DrawScreenFade(UCanvas* Canvas);

private:

	// Values used by our screen fading
	uint32 bFading : 1;
	uint32 bToBlack : 1; // Fading to black will be applied even if alpha is 1
	float FadeAlpha;
	float FadeStartTime;
	float FadeDuration;

};