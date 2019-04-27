#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Map.h"

//#include "Public/JsonStruct/MapStruct.h"
#include "Public/JsonStruct/PlayerStruct.h"

#include "ActionStruct.generated.h"

USTRUCT()
struct FMoveRequest
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FString playerID;

	UPROPERTY()
	int32 x;

	UPROPERTY()
	int32 y;

	FMoveRequest() {};
	FMoveRequest(int32 newPositionX, int32 newPositionY, FString movePlayerID)
		:x(newPositionX),
		y(newPositionY),
		playerID(movePlayerID)
	{};
};