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
	BlockSpacing = 200;

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
		const float XOffset = ( BlockIndex % Size ) * BlockSpacing + (75 * ((BlockIndex / Size) % 2)); // Divide by dimension
		const float YOffset =  BlockSpacing * (BlockIndex/Size); // Modulo gives remainder

																// Make position vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

		// Spawn a block
		AHexBlock* NewBlock = GetWorld()->SpawnActor<AHexBlock>(BlockLocation, FRotator(0, 0, 0));
	}

}

// Called every frame
void AHexGridGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

