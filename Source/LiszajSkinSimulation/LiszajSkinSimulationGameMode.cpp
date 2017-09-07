// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "LiszajSkinSimulation.h"
#include "LiszajSkinSimulationGameMode.h"
#include "LiszajSkinSimulationPlayerController.h"
#include "LiszajSkinSimulationPawn.h"

ALiszajSkinSimulationGameMode::ALiszajSkinSimulationGameMode()
{
	// no pawn by default
	DefaultPawnClass = ALiszajSkinSimulationPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = ALiszajSkinSimulationPlayerController::StaticClass();
}
