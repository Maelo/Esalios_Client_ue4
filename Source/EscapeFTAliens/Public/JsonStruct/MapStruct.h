
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Map.h"
#include "MapStruct.generated.h"

USTRUCT()
struct FSectorStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FString x;

	UPROPERTY()
	FString y;

	UPROPERTY()
	FString state;
};

USTRUCT()
struct FSize
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int x;

	UPROPERTY()
	int y;
};

USTRUCT()
struct FMapContent
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FString name;

	UPROPERTY()
	FSize size;

	UPROPERTY()
	TArray<FSectorStruct> sectorList;
};