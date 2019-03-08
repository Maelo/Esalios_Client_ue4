// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerRepresentation.generated.h"

class AHexBlock;

UCLASS()
class ESCAPEFTALIENS_API APlayerRepresentation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerRepresentation();

	void updatePosition(AHexBlock*);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class UStaticMeshComponent* Mesh;

	class UPlayerInfo* PlayerInfo;
	
};
