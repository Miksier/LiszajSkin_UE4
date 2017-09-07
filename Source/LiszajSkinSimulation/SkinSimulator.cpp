// Fill out your copyright notice in the Description page of Project Settings.

#include "LiszajSkinSimulation.h"
#include "SkinSimulator.h"
#include "SkinCell.h"
#include "LiszajSkinSimulationPawn.h"

// Sets default values
ASkinSimulator::ASkinSimulator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//	 Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Set defaults
	Size = 15;
	BlockSpacing = 300.f;
	SkinCells = TArray <ASkinCell*>();
	InfectionPropability = 50;
	ProtectionPeriod = 4;
	SickPeriod = 6;
	TimeTickInterval = 0.5f;
}

// Called when the game starts or when spawned
void ASkinSimulator::BeginPlay()
{
	Super::BeginPlay();
	GenerateSkin();
	cameraOnPlace = false;
}

// Called every frame
void ASkinSimulator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ((!SkinCells[0]->WasRecentlyRendered(0.1f) || !SkinCells[SkinCells.Num() - 1]->WasRecentlyRendered(0.1f)) && cameraOnPlace == false)
	{
		ALiszajSkinSimulationPawn* pawn = (ALiszajSkinSimulationPawn*)GetWorld()->GetFirstPlayerController()->GetPawn();
		pawn->CameraArm->TargetArmLength += CameraArmIncrementValue;
		cameraOnPlace = false;
	}
	else
	{
		cameraOnPlace = true;
	}
}

void ASkinSimulator::GenerateSkin()
{
	// Number of skin cells
	const int32 NumBlocks = Size * Size;
	// Offset to center the skin in dle middle of camera
	int offset = BlockSpacing * Size / 2;

	for (int32 cellsI = 0; cellsI < NumBlocks; cellsI++)
	{
		const float XOffset = (cellsI / Size) * BlockSpacing - offset; // Divide by dimension
		const float YOffset = (cellsI % Size) * BlockSpacing - offset; // Modulo gives remainder
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation(); // Make postion vector, offset from Grid location

		// Spawn a skin cell
		ASkinCell* skinCell = GetWorld()->SpawnActor<ASkinCell>(BlockLocation, FRotator(0, 0, 0));
		if (skinCell != nullptr)
		{
			skinCell->OwningGrid = this;
			skinCell->SickPeriod = SickPeriod;
			skinCell->ProtectionPeriod = ProtectionPeriod;
			skinCell->InfectionPropability = InfectionPropability;
			skinCell->GetNeighbours(cellsI, Size);
		}
		SkinCells.Add(skinCell);
	}
	GetWorld()->GetTimerManager().SetTimer(TimerTickHandle, this, &ASkinSimulator::TimeTick, TimeTickInterval, true, 0.0f);
}
void ASkinSimulator::TimeTick()
{
	TArray<int> sickCells = TArray<int>();
	for (int32 cellsI = 0; cellsI < SkinCells.Num(); cellsI++)
	{

		SkinCells[cellsI]->TimeTick();
		if (SkinCells[cellsI]->IsSick)
		{
			sickCells.Add(cellsI);
		}
	}
	for (int32 cellsI = 0; cellsI < sickCells.Num(); cellsI++)
	{
		TArray<int> neighbours = SkinCells[sickCells[cellsI]]->Neighbours;
		for (int i = 0; i < neighbours.Num(); i++)
		{
			SkinCells[neighbours[i]]->GetInfected();
		}

	}
}
