// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Misc/Paths.h"

#include "jsonMapParser.generated.h"


UCLASS()
class ESCAPEFTALIENS_API AjsonMapParser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AjsonMapParser();

public:	
	void ParseJson(FString jsonName);
};
