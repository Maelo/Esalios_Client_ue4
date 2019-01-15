// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeFTAliensGameModeBase.h"
#include "PlayerCamera.h"
#include "PlayerScrollerController.h"
#include "PlayerRepresentation.h"
#include "EngineUtils.h"
#include "Engine/World.h"

AEscapeFTAliensGameModeBase::AEscapeFTAliensGameModeBase()
{
	DefaultPawnClass = APlayerCamera::StaticClass();
	PlayerControllerClass = APlayerScrollerController::StaticClass();

	Init();
}

void AEscapeFTAliensGameModeBase::Init()
{
	//for (TActorIterator<APlayerRepresentation> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	//{
	//	// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
	//	APlayerRepresentation *Mesh = *ActorItr;
	//	FString actorName = Mesh->GetName();

	//	if (actorName.Compare("Player") == 0)
	//	{
	//		PlayerRepresentation = Mesh;
	//	}
	//}
}
