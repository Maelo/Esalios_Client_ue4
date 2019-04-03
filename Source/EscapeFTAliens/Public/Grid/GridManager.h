// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JsonStruct/MapStruct.h"
#include "Grid.h"

#include "GridManager.generated.h"

class AHexBlock;

UCLASS()
class ESCAPEFTALIENS_API AGridManager : public AActor
{
	GENERATED_BODY()
	
	/** Dummy root component */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	void GetMaterialRefs();

public:	
	// Sets default values for this actor's properties
	AGridManager();

	/** Number of blocks along each side of grid */
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	int32 Size;

	/** Spacing of blocks */
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	float BlockSpacingX;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	float BlockSpacingY;

	class UMaterialInstanceDynamic* SecureMaterial;
	UMaterialInstanceDynamic* DangerMaterial;
	UMaterialInstanceDynamic* BlockedMaterial;
	UMaterialInstanceDynamic* HumanMaterial;
	UMaterialInstanceDynamic* AlienMaterial;
	UMaterialInstanceDynamic* EscapeMaterial;

	void GenerateMap(const FMapContent& map);

	AHexBlock* GetHexBlock(FVector2D blockPosition);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }

private:

	FVector2D sizeMap;

	Grid grid;
};
