// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerRepresentation.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "UObjectGlobals.h"
#include "PlayerInfo.h"

// Sets default values
APlayerRepresentation::APlayerRepresentation()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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
	//PlayerInfo->UpdatePosition(11, 7);
	
}

// Called every frame
void APlayerRepresentation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

