// Fill out your copyright notice in the Description page of Project Settings.

#include "LiszajSkinSimulation.h"
#include "SkinCell.h"


// Sets default values
ASkinCell::ASkinCell()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial"))
			, BlueMaterial(TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"))
			, OrangeMaterial(TEXT("/Game/Puzzle/Meshes/OrangeMaterial.OrangeMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	Mesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	Mesh->SetRelativeScale3D(FVector(1.f, 1.f, 0.25f));
	Mesh->SetRelativeLocation(FVector(0.f, 0.f, 25.f));
	Mesh->SetMaterial(0, ConstructorStatics.BlueMaterial.Get());
	Mesh->SetupAttachment(DummyRoot);
	Mesh->OnClicked.AddDynamic(this, &ASkinCell::BlockClicked);

	// Save a pointer to the orange material
		BaseMaterial = ConstructorStatics.BaseMaterial.Get();
		BlueMaterial = ConstructorStatics.BlueMaterial.Get();
		OrangeMaterial = ConstructorStatics.OrangeMaterial.Get();
	Neighbours = TArray<int>();
}

void ASkinCell::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	MakeSick();
}

void ASkinCell::MakeSick()
{
	if (ProtectionPeriodLeft < 1 && !IsSick)
	{
		SickPeriodLeft = SickPeriod;
		SetColor("Orange");
	}

}
void ASkinCell::GetInfected()
{
	if (ProtectionPeriodLeft < 1 && !IsSick)
	{
		if (rand() % 100 + 1 <= InfectionPropability)
		{
			MakeSick();
		}
	}
}
void ASkinCell::TimeTick()
{
	if (IsSick)
	{
		if (SickPeriodLeft > 0)
		{
			SickPeriodLeft--;
		}
		if (SickPeriodLeft == 0)
		{
			ProtectionPeriodLeft = ProtectionPeriod;
			SetColor("Gray");
		}
	}
	else
	{
		if (ProtectionPeriodLeft > 0)
		{
			ProtectionPeriodLeft--;
		}
		if (ProtectionPeriodLeft == 0 && !IsHealthy)
		{
			SetColor("Blue");
		}
	}
}
void ASkinCell::SetColor(FString color)
{
	if (color == "Orange")
	{
		Mesh->SetMaterial(0, OrangeMaterial);
		IsSick = true;
		IsHealthy = false;
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Orange"));
	}
	else if (color == "Blue")
	{
		Mesh->SetMaterial(0, BlueMaterial);
		IsHealthy = true;
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Blue"));
	}
	else if (color == "Gray")
	{
		Mesh->SetMaterial(0, BaseMaterial);
		IsSick = false;
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Gray"));
	}
}
void ASkinCell::GetNeighbours(int cell,int Size)
{
	int xPosition = cell / Size;
	int yPosition = cell % Size;
	Neighbours.Empty();
	if (xPosition > 0)
	{
		Neighbours.Add(CreateNeighbours(xPosition - 1, yPosition, Size));
	}
	if (xPosition < Size - 1)
	{
		Neighbours.Add(CreateNeighbours(xPosition + 1, yPosition, Size));
	}
	if (yPosition > 0)
	{
		Neighbours.Add(CreateNeighbours(xPosition, yPosition - 1, Size));
	}
	if (yPosition < Size - 1)
	{
		Neighbours.Add(CreateNeighbours(xPosition, yPosition + 1, Size));
	}

	if (xPosition > 0 && yPosition > 0)
	{
		Neighbours.Add(CreateNeighbours(xPosition - 1, yPosition - 1, Size));
	}
	if (xPosition > 0 && yPosition < Size - 1)
	{
		Neighbours.Add(CreateNeighbours(xPosition - 1, yPosition + 1, Size));
	}
	if (xPosition < Size - 1 && yPosition > 0)
	{
		Neighbours.Add(CreateNeighbours(xPosition + 1, yPosition - 1,Size));
	}
	if (xPosition < Size - 1 && yPosition < Size - 1)
	{
		Neighbours.Add(CreateNeighbours(xPosition + 1, yPosition + 1, Size));
	}
}
int ASkinCell::CreateNeighbours(int x, int y,int Size)
{
	return x*Size + y;
}