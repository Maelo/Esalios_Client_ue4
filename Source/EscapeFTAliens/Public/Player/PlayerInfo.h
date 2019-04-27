// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInfo.generated.h"

class UHexCoordComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEFTALIENS_API UPlayerInfo : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInfo();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool UpdatePosition(const int x,const int y);

	const FString& GetUniqueID() { return uniqueID; }

	void SetUniqueID(const FString& newUniqueID);

private:
	// Current position of the player
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UHexCoordComponent* HexCoord;

	//UID
	FString uniqueID;

	// nb movement per turn
	int nbMovement;
	
	// Human? Alien?
	bool playerType;
};
