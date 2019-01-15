// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexBlock.h"
#include "GameManager.generated.h"

UCLASS()
class ESCAPEFTALIENS_API AGameManager : public AActor
{
	GENERATED_BODY()
	

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerMoveRequestEvent, AHexBlock*, block);
public:	
	// Sets default values for this actor's properties
	AGameManager();

	UFUNCTION()
	void MovePlayer(AHexBlock* block);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BlueprintAssignable, Category = "PlayerMoveEvent")
		FPlayerMoveRequestEvent OnPlayerMoveRequest;

	class APlayerRepresentation* PlayerRepresentation;
	
};
