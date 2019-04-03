#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Map.h"

#include "Public/JsonStruct/MapStruct.h"
#include "Public/JsonStruct/PlayerStruct.h"

#include "GameStruct.generated.h"

USTRUCT()
struct FGameStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FString uuid;

	UPROPERTY()
	FString map;

	UPROPERTY()
	FString date;

	UPROPERTY()
	FMapContent mapContent;

	UPROPERTY()
	FPlayers Players;
};