// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerScrollerController.h"

void APlayerScrollerController::SetupInputComponent()
{
	bShowMouseCursor = true;

	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;

}
