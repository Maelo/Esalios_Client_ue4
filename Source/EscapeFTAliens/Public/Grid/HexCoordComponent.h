// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HexCoord.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Map.h"
#include "HexCoordComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEFTALIENS_API UHexCoordComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHexCoordComponent();

private:
	HexCoord hexCoord_;

public:
	UHexCoordComponent(const TPair<int,int> coord) : hexCoord_(coord) {};

	void setCoord(const int x, const int y) { hexCoord_.setCoord( TPair<int, int>(x, y) ); }

	void setCoord(const TPair<int, int>& coord) { hexCoord_.setCoord(coord); }

	const HexCoord& getCoord() const { return hexCoord_; }
};

