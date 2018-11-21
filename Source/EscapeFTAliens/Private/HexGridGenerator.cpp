// Fill out your copyright notice in the Description page of Project Settings.

#include "HexGridGenerator.h"
#include "Engine/World.h"

#include "HexBlock.h"

#include "Json.h"
#include "JsonSerializer.h"
#include "FileManager.h"
#include "Misc/Paths.h"

// Sets default values
AHexGridGenerator::AHexGridGenerator()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Set defaults
	Size = 5;
	BlockSpacingX = 175;
	BlockSpacingY = 175;
}

// Called when the game starts or when spawned
void AHexGridGenerator::BeginPlay()
{
	Super::BeginPlay();

	FMapJson map = ParseMapJson("GALILEITest.json");


	for (int32 x = 0; x <= map.sizeMap.X; ++x)
	{
		for (int32 y = 0; y <= map.sizeMap.Y; ++y)
		{
			FSector*  blockSector = nullptr;
			for (int32 i = 0; i < map.sectorList.Num(); ++i)
			{
				FSector tempSector = map.sectorList[i];
				if (tempSector.x == x && tempSector.y == y)
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
				NewBlock->SetBlockType(blockSector->type);
			}
			else
			{
				NewBlock->SetBlockType(EBlockType::BT_BLOCKED);
			}
		}
	}
	// Number of blocks
	//const int32 NumBlocks = Size * Size;

	//// Loop to spawn each block
	//for (int32 BlockIndex = 0; BlockIndex<NumBlocks; BlockIndex++)
	//{
	//	const float XOffset = ( BlockIndex % Size ) * BlockSpacingX + 
	//								(87.5 * ((BlockIndex / Size) % 2)); //Used for the offset for the odd columns
	//	const float YOffset = -1 * BlockSpacingY * (BlockIndex/Size); // Modulo gives remainder

	//	// Make position vector, offset from Grid location
	//	const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

	//	// Spawn a block
	//	AHexBlock* NewBlock = GetWorld()->SpawnActor<AHexBlock>(BlockLocation, FRotator(0, 0, 0));

	//	//TODO Set coord here
	//	NewBlock->setCoord(BlockIndex / Size, BlockIndex % Size);
	//}

}

// Called every frame
void AHexGridGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FMapJson AHexGridGenerator::ParseMapJson(FString jsonName)
{
	FString contentFolder = FPaths::GameContentDir();
	FString JsonFilePath = contentFolder + "\\..\\Map\\" + jsonName;

	FString JsonString; //Json converted to FString

	FFileHelper::LoadFileToString(JsonString, *JsonFilePath);

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	FMapJson mapJson;

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		//The person "object" that is retrieved from the given json file
		TArray <TSharedPtr<FJsonValue>> sectorArray = JsonObject->GetArrayField("sectorList");

		mapJson.nameMap = JsonObject->GetStringField("name");

		TSharedPtr<FJsonObject> mapSizeJson = JsonObject->GetObjectField("size");

		mapJson.sizeMap.X = mapSizeJson->GetNumberField("x");
		mapJson.sizeMap.Y = mapSizeJson->GetNumberField("y");

		for (const auto& sector : sectorArray)
		{
			TSharedPtr<FJsonObject> sectorObj = sector->AsObject();

			int32 x = FCString::Atoi(*sectorObj->GetStringField("x"));
			int32 y = FCString::Atoi(*sectorObj->GetStringField("y"));
			FString strType = sectorObj->GetStringField("state");

			EBlockType blockType = EBlockType::BT_BLOCKED;

			if (strType.Equals(TEXT("dangerous")))
			{
				blockType = EBlockType::BT_DANGER;
			}
			else if (strType.Equals(TEXT("safe")))
			{
				blockType = EBlockType::BT_SECURE;
			}
			else if (strType.Equals(TEXT("hatch")))
			{
				blockType = EBlockType::BT_ESCAPE;
			}
			else if (strType.Equals(TEXT("human")))
			{
				blockType = EBlockType::BT_HUMAN;
			}
			else if (strType.Equals(TEXT("alien")))
			{
				blockType = EBlockType::BT_ALIEN;
			}

			mapJson.sectorList.Add(FSector(x, y, blockType));
		}
	}
	else
	{
		GLog->Log("couldn't deserialize");
	}

	return mapJson;
}

