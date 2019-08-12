// Fill out your copyright notice in the Description page of Project Settings.

#include "jsonMapParser.h"
#include "Json.h"
#include "JsonSerializer.h"
#include "FileManager.h"

// Sets default values
AjsonMapParser::AjsonMapParser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AjsonMapParser::ParseJson(FString jsonName)
{
	//TODO
	//Not used anymore, only for debugging purpose
	FString contentFolder = FPaths::GameContentDir();

	FString pathTojson = contentFolder + "\\..\\Map\\" + jsonName;
}

