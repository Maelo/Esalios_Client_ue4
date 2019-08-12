// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerRepresentation.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "UObjectGlobals.h"
#include "PlayerInfo.h"
#include "HexBlock.h"

// Sets default values
APlayerRepresentation::APlayerRepresentation()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//TODO, At the moment, the player representation is only a cube.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetStaticMesh(CubeMeshAsset.Object);

	RootComponent = Mesh;

	PlayerInfo = CreateDefaultSubobject<UPlayerInfo>("PlayerInfo0");
}

// Called when the game starts or when spawned
void APlayerRepresentation::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerRepresentation::updatePosition(AHexBlock* block)
{
	if (!block)
	{
		return;
	}

	SetActorLocation(block->GetActorLocation());

	//TODO
	//PlayerInfo->UpdatePosition(block->getCoord().getx(), block->getCoord().gety());
}

// Called every frame
void APlayerRepresentation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

