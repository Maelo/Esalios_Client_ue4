// Fill out your copyright notice in the Description page of Project Settings.

#include "HexBlock.h"

#include "HexCoord.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"


// Sets default values
AHexBlock::AHexBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("StaticMesh'/Game/hex.hex'"))
			, BaseMaterial(TEXT("Material'/Game/white.white'"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;
	RootComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	BlockMesh->SetWorldLocation(FVector(0.f, 0.f, 0.f));
	BlockMesh->SetupAttachment(DummyRoot);

	BlockMesh->SetMaterial(0, ConstructorStatics.BaseMaterial.Get());

}

// Called when the game starts or when spawned
void AHexBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHexBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

