// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Map.h"

#include "GridManager.h"

#include "HexCoordComponent.h"
#include "HexBlock.generated.h"

class UHexCoordComponent;
class UMaterialInstance;


USTRUCT(BlueprintType)
struct FBlockTypeMaterialInstanceStruct
{
	GENERATED_BODY()
};

UCLASS()
class ESCAPEFTALIENS_API AHexBlock : public AActor
{
	GENERATED_BODY()
private:
	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BlockMesh;

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UHexCoordComponent* HexCoordComponent;

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* PlayerPositionComponent;

	/*UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* TextRender;*/

	FString BlockType_;

public:	

	// Sets default values for this actor's properties
	AHexBlock();

	UFUNCTION(Category = "Collision")
		void OnCursorOver(UPrimitiveComponent* Component);

	UFUNCTION(Category = "Collision")
		void EndCursorOver(UPrimitiveComponent* Component);

	UFUNCTION(Category = "Collision")
		void OnClick(UPrimitiveComponent* ClickedComp, FKey ButtonPressed);

	const HexCoord& getCoord() const { return HexCoordComponent->getCoord(); };
	void setCoord(const int x, const int y);

	FString GetBlockType() { return BlockType_; }

	void SetBlockType(FString blockType, UMaterialInstanceDynamic* mat);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }

	/** Returns HexCoord subobject **/
	FORCEINLINE class UHexCoordComponent* GetHexCoord() const { return HexCoordComponent; }

	/** Returns TextRender subobject **/
	//FORCEINLINE class UTextRenderComponent* GetTextRender() const { return TextRender; }
};
