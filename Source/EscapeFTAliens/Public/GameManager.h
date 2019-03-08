// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Array.h"
#include "HexBlock.h"
#include "GameManager.generated.h"

class AServerManager;
class HttpRequest;

UCLASS()
class ESCAPEFTALIENS_API AGameManager : public AActor
{
	GENERATED_BODY()

	enum class GameState : uint8
	{
		Connecting 	UMETA(DisplayName = "Connecting"),
		Playing 	UMETA(DisplayName = "Playing"),
		EndGame	UMETA(DisplayName = "EndGame")
	};
	

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerMoveRequestEvent, AHexBlock*, block);
public:	
	// Sets default values for this actor's properties
	AGameManager();

	UFUNCTION()
	void MovePlayer(AHexBlock* block);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Tick(float DeltaTime);

public:	
	UPROPERTY(BlueprintAssignable, Category = "PlayerMoveEvent")
	FPlayerMoveRequestEvent OnPlayerMoveRequest;

	class APlayerRepresentation* PlayerRepresentation;

	class AGridManager* gridManager_;

	class AServerManager* ServerManager;

	TArray<TSharedPtr<HttpRequest>> WaitCalls_;

	GameState GameState_;
	
};
