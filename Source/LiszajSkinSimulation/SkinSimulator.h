// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SkinSimulator.generated.h"

UCLASS()
class LISZAJSKINSIMULATION_API ASkinSimulator : public AActor
{
	GENERATED_BODY()
	/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USceneComponent* DummyRoot;
public:	
	/** Number of blocks along each side of grid */
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
	int32 Size;
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
	int32 ProtectionPeriod;
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
	int32 SickPeriod;
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
	int32 InfectionPropability;
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
	float TimeTickInterval;
	/** Spacing of blocks */
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		float BlockSpacing;
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		float CameraArmIncrementValue;


	TArray < class ASkinCell* > SkinCells;
	FTimerHandle TimerTickHandle;
	bool cameraOnPlace;
	void GenerateSkin();
	void TimeTick();



	// Sets default values for this actor's properties
	ASkinSimulator();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;






	
};
