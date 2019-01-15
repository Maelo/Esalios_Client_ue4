// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "PlayerRepresentation.h"

#include "EngineUtils.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AGameManager::MovePlayer(AHexBlock* block)
{
	
	PlayerRepresentation->SetActorLocation(block->GetActorLocation());
	//PlayerRepresentation->
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	OnPlayerMoveRequest.AddDynamic(this, &AGameManager::MovePlayer);

	for (TActorIterator<APlayerRepresentation> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		APlayerRepresentation *Mesh = *ActorItr;
		FString actorName = Mesh->GetName();

		if (actorName.Compare("Player") == 0)
		{
			PlayerRepresentation = Mesh;
		}
	}

	if (PlayerRepresentation)
	{
		for (TActorIterator<AHexBlock> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
			AHexBlock *Mesh = *ActorItr;

			MovePlayer(Mesh);

			break;

			
		}
	}
}

