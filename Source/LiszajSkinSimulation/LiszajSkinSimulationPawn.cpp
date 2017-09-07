// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "LiszajSkinSimulation.h"
#include "LiszajSkinSimulationPawn.h"
#include "SkinCell.h"

ALiszajSkinSimulationPawn::ALiszajSkinSimulationPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraArm = CreateDefaultSubobject<USpringArmComponent>("CameraArm");
	RootComponent = CameraArm;
	Camera->AttachTo(CameraArm);
	CameraArm->TargetArmLength = 0;
	CameraArm->SetRelativeRotation(FRotator(270, 0, 0));
	Camera->Activate();
}

void ALiszajSkinSimulationPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ALiszajSkinSimulationPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
