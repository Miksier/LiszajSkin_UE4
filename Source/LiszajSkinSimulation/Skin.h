// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Skin.generated.h"

UCLASS()
class LISZAJSKINSIMULATION_API ASkin : public AActor
{
	GENERATED_BODY()
	/** Dummy root component */
	//UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//	class USceneComponent* DummyRoot;
public:
	ASkin();


	/** Number of blocks along each side of grid */
	/*UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
		int32 Size;
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
		int32 ProtectionPeriod;
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
		int32 SickPeriod;
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
		int32 InfectionPropability;
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
		float TimeTickInterval;*/

	//TArray < class ASkinCell* > SkinCells;

	/** Spacing of blocks */
	//UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	//	float BlockSpacing;

	//void GenerateSkin();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// End AActor interface

private:
	//FTimerHandle TimerTickHandle;
	void TimeTick();
};
