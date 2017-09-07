// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "LiszajSkinSimulation.h"
#include "LiszajSkinSimulationPlayerController.h"

ALiszajSkinSimulationPlayerController::ALiszajSkinSimulationPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
