// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModeEftaios.h"

#include "PlayerCamera.h"
#include "PlayerScrollerController.h"

AGameModeEftaios::AGameModeEftaios(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultPawnClass = APlayerCamera::StaticClass();
	PlayerControllerClass = APlayerScrollerController::StaticClass();
}