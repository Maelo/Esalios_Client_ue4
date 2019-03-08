// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "EngineUtils.h"

#include "PlayerRepresentation.h"
#include "ServerCommandManager/Server.h"
#include "PlayerInfo.h"
#include "HexCoord.h"
#include "EscapeFTAliens/ServerCommandManager/Request/GetRequest.h"
#include "EscapeFTAliens/ServerCommandManager/Request/PostRequest.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AGameManager::MovePlayer(AHexBlock* block)
{
	PlayerRepresentation->updatePosition(block);
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	OnPlayerMoveRequest.AddDynamic(this, &AGameManager::MovePlayer);

	for (TActorIterator<APlayerRepresentation> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		APlayerRepresentation *player = *ActorItr;
		FString actorName = player->GetName();

		if (actorName.Compare("Player") == 0)
		{
			PlayerRepresentation = player;
		}
	}

	for (TActorIterator<AServerManager> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		ServerManager = *ActorItr;
	}

	for (TActorIterator<AGridManager> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		gridManager_ = *ActorItr;
	}

	/*TSharedPtr <GetPlayerRequest> getPlayerInfo(new GetPlayerRequest());
	ServerManager->sendCall(getPlayerInfo);
	WaitCalls_.Add(getPlayerInfo);*/

	TSharedPtr <PostGameRequest> postGame(new PostGameRequest());
	ServerManager->sendCall(postGame);
	WaitCalls_.Add(postGame);
}


// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	for (TSharedPtr<HttpRequest> call: WaitCalls_)
	{
		if (call->receivedResponse())
		{
			////TEST Get Player
			/*GetPlayerRequest* getPlayerRequest = (GetPlayerRequest*)(call.Get());

			getPlayerRequest->parseJsonResponse();

			FVector2D playerPosition = getPlayerRequest->getPosition();

			AHexBlock* block = gridManager_->GetHexBlock(playerPosition);

			MovePlayer(block);*/
			////

			////TEST Post Game Request
			PostGameRequest* postgameRequest = (PostGameRequest*)(call.Get());

			postgameRequest->parseJsonResponse();

			gridManager_->GenerateMap(postgameRequest->getMap());
			////


			call->setHandledResponse(true);
		}
	}


	for (int i = WaitCalls_.Num() - 1; i >= 0; --i)
	{
		if (WaitCalls_[i]->isHandled())
		{
			WaitCalls_.RemoveAt(i);
		}
	}
}

