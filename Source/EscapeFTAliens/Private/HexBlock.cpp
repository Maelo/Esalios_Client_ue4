// Fill out your copyright notice in the Description page of Project Settings.

#include "HexBlock.h"

#include "HexCoordComponent.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "PhysicsEngine/BodySetup.h"


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

	//BlockMesh->SetMaterial(0, SecureMaterial);

	HexCoord = CreateDefaultSubobject<UHexCoordComponent>(TEXT("HexCoord0"));
	//HexCoord->SetupAttachment(DummyRoot);

	/*TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextCoord0"));
	TextRender->SetupAttachment(DummyRoot);
	TextRender->SetTextRenderColor(FColor::Red);
	TextRender->SetRelativeLocationAndRotation(FVector(20.f, 25.f, 6.f), FRotator(90.f, 0.f, 0.f));*/
	//TextRender->SetWorldLocationAndRotation(FVector(20.f, 25.f, 6.f), FRotator(90.f, 0.f, 0.f));
}



//AHexBlock::AHexBlock(FVector2D blockCoord, EBlockType blockType)
//{
//	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//
//	//GetMaterialRefs();
//
//	struct FConstructorStatics
//	{
//		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
//
//		FConstructorStatics()
//			: PlaneMesh(TEXT("StaticMesh'/Game/hex.hex'"))
//		{
//		}
//	};
//	static FConstructorStatics ConstructorStatics;
//
//	// Create static mesh component
//	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
//	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
//	BlockMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
//	BlockMesh->SetWorldLocation(FVector(0.f, 0.f, 0.f));
//	BlockMesh->SetupAttachment(GetRootComponent());
//
//	SetBlockType(blockType);
//
//	UMaterialInstanceDynamic * DynMaterial = nullptr;
//
//	switch (blockType)
//	{
//	case EBlockType::BT_SECURE:
//		DynMaterial = UMaterialInstanceDynamic::Create(SecureMaterial, this);
//		BlockMesh->SetMaterial(0, DynMaterial);
//		break;
//	case EBlockType::BT_DANGER:
//		DynMaterial = UMaterialInstanceDynamic::Create(DangerMaterial, this);
//		BlockMesh->SetMaterial(0, DynMaterial);
//		break;
//	case EBlockType::BT_HUMAN:
//		DynMaterial = UMaterialInstanceDynamic::Create(HumanMaterial, this);
//		BlockMesh->SetMaterial(0, DynMaterial);
//		//BlockMesh->CreateAndSetMaterialInstanceDynamicFromMaterial
//		//BlockMesh->SetMaterial(0, HumanMaterial);
//		break;
//	case EBlockType::BT_ALIEN:
//		DynMaterial = UMaterialInstanceDynamic::Create(AlienMaterial, this);
//		BlockMesh->SetMaterial(0, DynMaterial);
//		//BlockMesh->SetMaterial(0, AlienMaterial);
//		break;
//	case EBlockType::BT_ESCAPE:
//		DynMaterial = UMaterialInstanceDynamic::Create(EscapeMaterial, this);
//		BlockMesh->SetMaterial(0, DynMaterial);
//		//BlockMesh->SetMaterial(0, EscapeMaterial);
//		break;
//	case EBlockType::BT_BLOCKED:
//		DynMaterial = UMaterialInstanceDynamic::Create(BlockedMaterial, this);
//		BlockMesh->SetMaterial(0, DynMaterial);
//		//BlockMesh->SetMaterial(0, BlockedMaterial);
//		break;
//	default:
//		DynMaterial = UMaterialInstanceDynamic::Create(BlockedMaterial, this);
//		BlockMesh->SetMaterial(0, DynMaterial);
//		//BlockMesh->SetMaterial(0, BlockedMaterial);
//		break;
//	}
//
//	HexCoord = CreateDefaultSubobject<UHexCoordComponent>(TEXT("HexCoord0"));
//
//	/*TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextCoord0"));
//	TextRender->SetupAttachment(GetRootComponent());
//	TextRender->SetTextRenderColor(FColor::Red);
//	TextRender->SetRelativeLocationAndRotation(FVector(20.f, 25.f, 6.f), FRotator(90.f, 0.f, 0.f));
//
//	FVector test(TextRender->GetComponentLocation());*/
//
//	setCoord(blockCoord.X, blockCoord.Y);
//	
//}

void AHexBlock::OnCursorOver(UPrimitiveComponent * Component)
{
	//UE_LOG(LogTemp, Warning, TEXT("Yoyo!!"));
	UE_LOG(LogTemp, Warning, TEXT("Block Type: %d, %d"), GetHexCoord()->getx(), GetHexCoord()->gety());

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
	
}

// Called every frame
void AHexBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

