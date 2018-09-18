// Fill out your copyright notice in the Description page of Project Settings.

#include "HexGridGenerator.h"
#include "Engine/World.h"

#include "HexBlock.h"

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

	// Number of blocks
	const int32 NumBlocks = Size * Size;

	// Loop to spawn each block
	for (int32 BlockIndex = 0; BlockIndex<NumBlocks; BlockIndex++)
	{
		const float XOffset = ( BlockIndex % Size ) * BlockSpacingX + 
									(87.5 * ((BlockIndex / Size) % 2)); //Used for the offset for the odd columns
		const float YOffset = -1 * BlockSpacingY * (BlockIndex/Size); // Modulo gives remainder

																// Make position vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

		// Spawn a block
		AHexBlock* NewBlock = GetWorld()->SpawnActor<AHexBlock>(BlockLocation, FRotator(0, 0, 0));

		//TODO Set coord here
		NewBlock->setCoord(BlockIndex / Size, BlockIndex % Size);
	}

}

// Called every frame
void AHexGridGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

