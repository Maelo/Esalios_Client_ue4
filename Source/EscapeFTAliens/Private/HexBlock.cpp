// Fill out your copyright notice in the Description page of Project Settings.

#include "HexBlock.h"

#include "HexCoordComponent.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstanceConstant.h"


// Sets default values
AHexBlock::AHexBlock()
{
	GetMaterialRefs();

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

	//BlockMesh->SetMaterial(0, SecureMaterial);

	HexCoord = CreateDefaultSubobject<UHexCoordComponent>(TEXT("HexCoord0"));
	//HexCoord->SetupAttachment(DummyRoot);

	/*TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextCoord0"));
	TextRender->SetupAttachment(DummyRoot);
	TextRender->SetTextRenderColor(FColor::Red);
	TextRender->SetRelativeLocationAndRotation(FVector(20.f, 25.f, 6.f), FRotator(90.f, 0.f, 0.f));*/
	//TextRender->SetWorldLocationAndRotation(FVector(20.f, 25.f, 6.f), FRotator(90.f, 0.f, 0.f));
}

void AHexBlock::GetMaterialRefs()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> SecureMat(TEXT("MaterialInstanceConstant'/Game/Materials/Blocks/SECURE.SECURE'"));
	if (SecureMat.Object != NULL)
	{
		SecureMaterial = (UMaterialInstanceConstant*)SecureMat.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> DangerMat(TEXT("MaterialInstanceConstant'/Game/Materials/Blocks/DANGEROUS.DANGEROUS'"));
	if (DangerMat.Object != NULL)
	{
		DangerMaterial = (UMaterialInstanceConstant*)DangerMat.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> BlockedMat(TEXT("MaterialInstanceConstant'/Game/Materials/Blocks/BLOCKED.BLOCKED'"));
	if (BlockedMat.Object != NULL)
	{
		BlockedMaterial = (UMaterialInstanceConstant*)BlockedMat.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> HumanMat(TEXT("MaterialInstanceConstant'/Game/Materials/Blocks/HUMAN.HUMAN'"));
	if (HumanMat.Object != NULL)
	{
		HumanMaterial = (UMaterialInstanceConstant*)HumanMat.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> AlienMat(TEXT("MaterialInstanceConstant'/Game/Materials/Blocks/ALIEN.ALIEN'"));
	if (AlienMat.Object != NULL)
	{
		AlienMaterial = (UMaterialInstanceConstant*)AlienMat.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> EscapeMat(TEXT("MaterialInstanceConstant'/Game/Materials/Blocks/ESCAPE.ESCAPE'"));
	if (EscapeMat.Object != NULL)
	{
		EscapeMaterial = (UMaterialInstanceConstant*)EscapeMat.Object;
	}
}

AHexBlock::AHexBlock(FVector2D blockCoord, EBlockType blockType)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMaterialRefs();

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;

		FConstructorStatics()
			: PlaneMesh(TEXT("StaticMesh'/Game/hex.hex'"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	BlockMesh->SetWorldLocation(FVector(0.f, 0.f, 0.f));
	BlockMesh->SetupAttachment(GetRootComponent());

	SetBlockType(blockType);

	switch (blockType)
	{
	case EBlockType::BT_SECURE:
		BlockMesh->SetMaterial(0, SecureMaterial);
		break;
	case EBlockType::BT_DANGER:
		BlockMesh->SetMaterial(0, DangerMaterial);
		break;
	case EBlockType::BT_HUMAN:
		BlockMesh->SetMaterial(0, HumanMaterial);
		break;
	case EBlockType::BT_ALIEN:
		BlockMesh->SetMaterial(0, AlienMaterial);
		break;
	case EBlockType::BT_ESCAPE:
		BlockMesh->SetMaterial(0, EscapeMaterial);
		break;
	case EBlockType::BT_BLOCKED:
		BlockMesh->SetMaterial(0, BlockedMaterial);
		break;
	default:
		BlockMesh->SetMaterial(0, BlockedMaterial);
		break;
	}

	HexCoord = CreateDefaultSubobject<UHexCoordComponent>(TEXT("HexCoord0"));

	/*TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextCoord0"));
	TextRender->SetupAttachment(GetRootComponent());
	TextRender->SetTextRenderColor(FColor::Red);
	TextRender->SetRelativeLocationAndRotation(FVector(20.f, 25.f, 6.f), FRotator(90.f, 0.f, 0.f));

	FVector test(TextRender->GetComponentLocation());*/

	setCoord(blockCoord.X, blockCoord.Y);
	
}

TPair<int, int> AHexBlock::getCoord() const
{
	return HexCoord->getCoord();
}

void AHexBlock::setCoord(const int x, const int y)
{
	HexCoord->setCoord(x, y);
	
	//FText coordText = FText::FromString(FString("(" + FString::FromInt(x) + "," + FString::FromInt(y) + ")"));
	//GetTextRender()->SetText(coordText);
}

void AHexBlock::SetBlockType(EBlockType blockType)
{
	BlockType_ = blockType;

	switch (blockType)
	{
	case EBlockType::BT_SECURE:
		BlockMesh->SetMaterial(0, SecureMaterial);
		break;
	case EBlockType::BT_DANGER:
		BlockMesh->SetMaterial(0, DangerMaterial);
		break;
	case EBlockType::BT_HUMAN:
		BlockMesh->SetMaterial(0, HumanMaterial);
		break;
	case EBlockType::BT_ALIEN:
		BlockMesh->SetMaterial(0, AlienMaterial);
		break;
	case EBlockType::BT_ESCAPE:
		BlockMesh->SetMaterial(0, EscapeMaterial);
		break;
	case EBlockType::BT_BLOCKED:
		BlockMesh->SetMaterial(0, BlockedMaterial);
		break;
	default:
		BlockMesh->SetMaterial(0, SecureMaterial);
		break;
	}

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

