// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerInfo.h"

#include "HexCoordComponent.h"

// Sets default values for this component's properties
UPlayerInfo::UPlayerInfo()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerInfo::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerInfo::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UPlayerInfo::UpdatePosition(const int x, const int y)
{
	HexCoord->setCoord(x, y);

	return true;
}

