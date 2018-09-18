// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	int x_, y_;

public:
	UHexCoordComponent(int x, int y) : x_(x), y_(y) {};

	void setx(int x) { x_ = x; }
	void sety(int y) { x_ = y; }

	void setCoord(const int x, const int y) { x_ = x; y_ = y; }

	const int getx() const { return x_; }
	const int gety() const { return y_; }

	const TPair<int, int> getCoord() const { return TPair<int, int>(x_, y_); }
};
