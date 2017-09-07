// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "LiszajSkinSimulationPawn.generated.h"

UCLASS(config = Game)
class ALiszajSkinSimulationPawn : public APawn
{
	GENERATED_UCLASS_BODY()
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadWrite)
		class UCameraComponent* Camera;
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadWrite)
		class USpringArmComponent* CameraArm;
public:

	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
