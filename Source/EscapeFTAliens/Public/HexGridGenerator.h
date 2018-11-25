// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexGridGenerator.generated.h"


UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EBlockType : uint8
{
	BT_SECURE 	UMETA(DisplayName = "Secure Sector"),
	BT_DANGER 	UMETA(DisplayName = "Dangerous Sector"),
	BT_HUMAN	UMETA(DisplayName = "Human Sector"),
	BT_ALIEN	UMETA(DisplayName = "Alien Sector"),
	BT_ESCAPE	UMETA(DisplayName = "Escape Sector"),
	BT_BLOCKED	UMETA(DisplayName = "Blocked Sector")
};

USTRUCT()
struct FSector
{
	GENERATED_USTRUCT_BODY()

		FSector() {};

	FSector(int x_, int y_, EBlockType type_) : x(x_), y(y_), type(type_) {};

	UPROPERTY()
	int x;

	UPROPERTY()
	int y;

	UPROPERTY()
	EBlockType type;

	bool operator==(const FSector& other) const
	{
		if (x == other.x && y == other.y)
		{
			return true;
		}
		return false;
	}
};

USTRUCT()
struct FMapJson
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FString nameMap;

	UPROPERTY()
	TArray<FSector> sectorList;

	UPROPERTY()
	FVector2D sizeMap;
};

UCLASS()
class ESCAPEFTALIENS_API AHexGridGenerator : public AActor
{
	GENERATED_BODY()
	
	/** Dummy root component */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	void GetMaterialRefs();

public:	
	// Sets default values for this actor's properties
	AHexGridGenerator();

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FMapJson ParseMapJson(FString jsonName);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
};
