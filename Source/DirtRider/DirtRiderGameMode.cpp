// Copyright Epic Games, Inc. All Rights Reserved.

#include "DirtRiderGameMode.h"
#include "DirtRiderPawn.h"
#include "DirtRiderHud.h"

ADirtRiderGameMode::ADirtRiderGameMode()
{
	DefaultPawnClass = ADirtRiderPawn::StaticClass();
	HUDClass = ADirtRiderHud::StaticClass();
}
