// Fill out your copyright notice in the Description page of Project Settings.

#include "GridManager.h"
#include "Engine/World.h"

#include "UObject/ConstructorHelpers.h"
#include "Public/EngineUtils.h"
#include "HexBlock.h"

#include "Utilities/JsonParser.h"

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
	BlockSpacingX = 175;
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

void AGridManager::GenerateMap(EFTAMap * map)
{
	const TArray<FSector> sectorList = map->getSectorList();

	sizeMap = map->getSize();

	grid.AddUninitialized(sizeMap.X + 1, sizeMap.Y + 1);

	for (int32 x = 0; x <= sizeMap.X; ++x)
	{
		for (int32 y = 0; y <= sizeMap.Y; ++y)
		{
			FSector*  blockSector = nullptr;
			for (int32 i = 0; i < sectorList.Num(); ++i)
			{
				FSector tempSector = sectorList[i];
				if (tempSector.getX() == x && tempSector.getY() == y)
				{
					blockSector = &tempSector;
					break;
				}
			}

			//TODO
			const float XOffset = -1 * x * BlockSpacingX  /*+ (-87.5 * (x % 2)) /*+ (87.5 * ((x / Size) % 2)) /*(BlockIndex % Size) * BlockSpacingX +
				(87.5 * ((BlockIndex / Size) % 2))*/; //Used for the offset for the odd columns
			const float YOffset = y * BlockSpacingY + (87.5 * (x % 2))/*-1 * BlockSpacingY * (BlockIndex / Size)*/; // Modulo gives remainder

																			// Make position vector, offset from Grid location
			const FVector BlockLocation = FVector(YOffset, XOffset, 0.f) + GetActorLocation();

			FActorSpawnParameters test;
			// Spawn a block
			AHexBlock* NewBlock = GetWorld()->SpawnActor<AHexBlock>(BlockLocation, FRotator(0, 0, 0));

			NewBlock->setCoord(x, y);

			if (blockSector)
			{
				switch (blockSector->type)
				{
				case EBlockType::BT_SECURE:
					NewBlock->SetBlockType(blockSector->type, SecureMaterial);
					break;
				case EBlockType::BT_DANGER:
					NewBlock->SetBlockType(blockSector->type, DangerMaterial);
					break;
				case EBlockType::BT_HUMAN:
					NewBlock->SetBlockType(blockSector->type, HumanMaterial);
					break;
				case EBlockType::BT_ALIEN:
					NewBlock->SetBlockType(blockSector->type, AlienMaterial);
					break;
				case EBlockType::BT_ESCAPE:
					NewBlock->SetBlockType(blockSector->type, EscapeMaterial);
					break;
				case EBlockType::BT_BLOCKED:
					NewBlock->SetBlockType(blockSector->type, BlockedMaterial);
					break;
				default:
					NewBlock->SetBlockType(blockSector->type, SecureMaterial);
					break;
				}
			}
			else
			{
				NewBlock->SetBlockType(EBlockType::BT_BLOCKED, BlockedMaterial);
			}

			grid.Rows[x].Columns[y] = NewBlock->GetName();
		}
	}
}

// Called when the game starts or when spawned
void AGridManager::BeginPlay()
{
	Super::BeginPlay();

	//TESTING CODE, generate Map locally (from local json)
	/*EFTAMap* map;

	map = EFTAJsonParser::ParseMapJson("GALILEITest.json");

	GenerateMap(map);*/
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
