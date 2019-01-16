// Fill out your copyright notice in the Description page of Project Settings.

#include "HexBlock.h"



#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "PhysicsEngine/BodySetup.h"

#include "GameManager.h"
#include "EngineUtils.h"

// Sets default values
AHexBlock::AHexBlock()
{
	//GetMaterialRefs();

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		FConstructorStatics()
			: PlaneMesh(TEXT("StaticMesh'/Game/hex.hex'"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent0"));
	SetRootComponent(DummyRoot);

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	BlockMesh->SetWorldLocation(FVector(0.f, 0.f, 0.f));
	BlockMesh->SetupAttachment(DummyRoot);

	BlockMesh->GetBodySetup()->CollisionTraceFlag = ECollisionTraceFlag::CTF_UseSimpleAsComplex;

	HexCoordComponent = CreateDefaultSubobject<UHexCoordComponent>(TEXT("HexCoord0"));

	PlayerPositionComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerPosition0"));
	PlayerPositionComponent->SetRelativeLocation(FVector(0.f, 0.f, 30.f));
	PlayerPositionComponent->SetupAttachment(DummyRoot);
}

void AHexBlock::OnCursorOver(UPrimitiveComponent * Component)
{
	UMaterialInstanceDynamic * mat = Cast<UMaterialInstanceDynamic>(BlockMesh->GetMaterial(0));
	if (mat)
	{
		mat->SetScalarParameterValue("metallic", 1.f);
	}
}

void AHexBlock::EndCursorOver(UPrimitiveComponent * Component)
{
	UMaterialInstanceDynamic * mat = Cast<UMaterialInstanceDynamic>(BlockMesh->GetMaterial(0));
	if (mat)
	{
		mat->SetScalarParameterValue("metallic", 0.f);
	}
}

void AHexBlock::OnClick(UPrimitiveComponent* ClickedComp, FKey ButtonPressed)
{
	AGameManager *GameManager = nullptr;

	for (TActorIterator<AGameManager> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		GameManager = *ActorItr;
		break;
	}

	if (GameManager)
	{
		GameManager->OnPlayerMoveRequest.Broadcast(this);
	}
}

void AHexBlock::setCoord(const int x, const int y)
{
	HexCoordComponent->setCoord(x, y);
}

void AHexBlock::SetBlockType(EBlockType blockType, UMaterialInstanceDynamic* mat)
{
	BlockType_ = blockType;
	BlockMesh->CreateAndSetMaterialInstanceDynamicFromMaterial(0, mat);
}

// Called when the game starts or when spawned
void AHexBlock::BeginPlay()
{
	Super::BeginPlay();

	BlockMesh->OnBeginCursorOver.AddDynamic(this, &AHexBlock::OnCursorOver);
	BlockMesh->OnEndCursorOver.AddDynamic(this, &AHexBlock::EndCursorOver);
	BlockMesh->OnClicked.AddDynamic(this, &AHexBlock::OnClick);
	
}

// Called every frame
void AHexBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

