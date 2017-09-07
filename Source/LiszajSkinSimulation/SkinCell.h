// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SkinCell.generated.h"

UCLASS()
class LISZAJSKINSIMULATION_API ASkinCell : public AActor
{
	GENERATED_BODY()

		/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* DummyRoot;
	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;

public:
	ASkinCell();

	bool IsSick;
	bool IsHealthy;

	int SickPeriod;
	int ProtectionPeriod;
	int SickPeriodLeft;
	int ProtectionPeriodLeft;
	float InfectionPropability;

	TArray<int> Neighbours;

	/** Pointer to white material used on the focused block */
	UPROPERTY()
		UMaterial* BaseMaterial;
	/** Pointer to blue material used on inactive blocks */
	UPROPERTY()
		UMaterialInstance* BlueMaterial;
	/** Pointer to orange material used on active blocks */
	UPROPERTY()
		UMaterialInstance* OrangeMaterial;
	/** Grid that owns us */
	UPROPERTY()
		class ASkinSimulator* OwningGrid;
	/** Handle the block being clicked */
	UFUNCTION()
		void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	void SetColor(FString color);
public:

	void MakeSick();
	void GetInfected();
	void TimeTick();

	void GetNeighbours(int cell,int Size);
	int CreateNeighbours(int x, int y,int Size);
};
