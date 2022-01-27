// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/HUD.h"
#include "DirtRiderHud.generated.h"


UCLASS(config = Game)
class ADirtRiderHud : public AHUD
{
	GENERATED_BODY()

public:
	ADirtRiderHud();

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface
};
