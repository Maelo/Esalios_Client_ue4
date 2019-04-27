
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Map.h"
#include "PlayerStruct.generated.h"

USTRUCT()
struct FPlayerStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FString uuid;

	UPROPERTY()
	FString username;

	UPROPERTY()
	FString joinDate;

	UPROPERTY()
	bool gameMaster;
};

USTRUCT()
struct FPlayers
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TArray<FPlayerStruct> players;
};

USTRUCT()
struct FPlayerID
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FString playerID;
};

USTRUCT()
struct FPlayerPosition
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int x;

	UPROPERTY()
	int y;
};