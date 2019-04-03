// Fill out your copyright notice in the Description page of Project Settings.

#include "GridManager.h"
#include "Engine/World.h"

#include "UObject/ConstructorHelpers.h"
#include "Public/EngineUtils.h"
#include "HexBlock.h"

#include "JsonStruct/MapStruct.h"

#include "FileManager.h"
#include "Misc/Paths.h"

// Sets default values
AGridManager::AGridManager()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Set defaults
	Size = 5;
	BlockSpacingX = 155;
	BlockSpacingY = 175;

	GetMaterialRefs();
}

AHexBlock * AGridManager::GetHexBlock(FVector2D blockPosition)
{
	if (blockPosition.X >= sizeMap.X || blockPosition.Y >= sizeMap.Y)
	{
		return nullptr;
	}

	FString blockName = grid.Rows[blockPosition.X].Columns[blockPosition.Y];

	for (TActorIterator<AHexBlock> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->GetName().Equals(blockName))
		{
			return *ActorItr;
		}
	}
	return nullptr;
}

void AGridManager::GenerateMap(const FMapContent& map)
{
	sizeMap = FVector2D(map.size.x, map.size.y);
	grid.AddUninitialized(sizeMap.X + 1, sizeMap.Y + 1);

	for (int32 x = 0; x <= sizeMap.X; ++x)
	{
		for (int32 y = 0; y < sizeMap.Y; ++y)
		{
			int idxFound = -1;
			for (int32 i = 0; i < map.sectorList.Num(); ++i)
			{
				if (FCString::Atoi(*map.sectorList[i].x) == x && FCString::Atoi(*map.sectorList[i].y) == y)
				{
					idxFound = i;
					break;
				}
			}

			const float XOffset = -1 * x * BlockSpacingX;
			const float YOffset = y * BlockSpacingY + (87.5 * (x % 2));

																			// Make position vector, offset from Grid location
			const FVector BlockLocation = FVector(YOffset, XOffset, 0.f);// + GetActorLocation();

			
			// Spawn a block
			AHexBlock* NewBlock = GetWorld()->SpawnActor<AHexBlock>(BlockLocation, FRotator(0, 0, 0));

			NewBlock->setCoord(x, y);

			if (idxFound != -1)
			{
				auto blockSector = map.sectorList[idxFound];
				if (blockSector.state == "safe")
				{
					NewBlock->SetBlockType(blockSector.state, SecureMaterial);
				}
				else if (blockSector.state == "dangerous")
				{
					NewBlock->SetBlockType(blockSector.state, DangerMaterial);
				}
				else if (blockSector.state == "hatch")
				{
					NewBlock->SetBlockType(blockSector.state, EscapeMaterial);
				}
				else if (blockSector.state == "alien")
				{
					NewBlock->SetBlockType(blockSector.state, AlienMaterial);
				}
				else if (blockSector.state == "human")
				{
					NewBlock->SetBlockType(blockSector.state, HumanMaterial);
				}
				else {
					NewBlock->SetBlockType(blockSector.state, BlockedMaterial);
				}
			}
			else
			{
				NewBlock->SetBlockType("blocked", BlockedMaterial);
			}

			grid.Rows[x].Columns[y] = NewBlock->GetName();
		}
	}
}

// Called when the game starts or when spawned
void AGridManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGridManager::GetMaterialRefs()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> SecureMat(TEXT("MaterialInstanceDynamic'/Game/Materials/Blocks/SECURE.SECURE'"));
	if (SecureMat.Object != NULL)
	{
		SecureMaterial = (UMaterialInstanceDynamic*)SecureMat.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> DangerMat(TEXT("MaterialInstanceDynamic'/Game/Materials/Blocks/DANGEROUS.DANGEROUS'"));
	if (DangerMat.Object != NULL)
	{
		DangerMaterial = (UMaterialInstanceDynamic*)DangerMat.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> BlockedMat(TEXT("MaterialInstanceDynamic'/Game/Materials/Blocks/BLOCKED.BLOCKED'"));
	if (BlockedMat.Object != NULL)
	{
		BlockedMaterial = (UMaterialInstanceDynamic*)BlockedMat.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> HumanMat(TEXT("MaterialInstanceDynamic'/Game/Materials/Blocks/HUMAN.HUMAN'"));
	if (HumanMat.Object != NULL)
	{
		HumanMaterial = (UMaterialInstanceDynamic*)HumanMat.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> AlienMat(TEXT("MaterialInstanceDynamic'/Game/Materials/Blocks/ALIEN.ALIEN'"));
	if (AlienMat.Object != NULL)
	{
		AlienMaterial = (UMaterialInstanceDynamic*)AlienMat.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> EscapeMat(TEXT("MaterialInstanceDynamic'/Game/Materials/Blocks/ESCAPE.ESCAPE'"));
	if (EscapeMat.Object != NULL)
	{
		EscapeMaterial = (UMaterialInstanceDynamic*)EscapeMat.Object;
	}
}
