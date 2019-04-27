#pragma once
#include "CoreMinimal.h"
#include "JsonStruct/MapStruct.h"
#include "JsonStruct/PlayerStruct.h"
#include "JsonStruct/MapStruct.h"

#include "EscapeFTAliens/Public/HttpClient/Request/Request.h"

class GetPlayerPositionRequest : public HttpRequest
{
public:
	GetPlayerPositionRequest(FString uniqueID)
		: HttpRequest("/getPlayerPosition", HttpRequest::GET, "GetPlayerPosition")
	{
		addParam(TPair<FString, FString>("playerID", uniqueID));
	}

	virtual void parseJsonResponse()
	{
		TSharedPtr<FJsonObject> json = getObjectResponse();
		playerPosition = MakeShareable(new FPlayerPosition);

		FJsonObjectConverter::JsonObjectToUStruct<FPlayerPosition>(
			json.ToSharedRef(),
			playerPosition.Get(), 0, 0);
	}

	const TSharedPtr<FPlayerPosition>& getPlayerPosition() { return playerPosition; }

private:
	TSharedPtr<FPlayerPosition> playerPosition;
};

class GetMapRequest : public HttpRequest
{
public:
	GetMapRequest(FString gameID)
		: HttpRequest("/map", HttpRequest::GET, "GetMap")
	{
		addParam(TPair<FString, FString>("gameID", gameID));
	}

	virtual void parseJsonResponse()
	{
		TSharedPtr<FJsonObject> json = getObjectResponse();
		mapContent = MakeShareable(new FMapContent);

		FJsonObjectConverter::JsonObjectToUStruct<FMapContent>(
			json.ToSharedRef(),
			mapContent.Get(), 0, 0);
	}

	const TSharedPtr<FMapContent>& getMapContent() { return mapContent; }

private:
	TSharedPtr<FMapContent> mapContent;
};

class GetPlayerTurn : public HttpRequest
{
public:
	GetPlayerTurn()
		: HttpRequest("/turn", HttpRequest::GET, "GetTurn")
	{
	}

	virtual void parseJsonResponse()
	{
		TSharedPtr<FJsonObject> json = getObjectResponse();
		playerTurn = MakeShareable(new FPlayerID);

		FJsonObjectConverter::JsonObjectToUStruct<FPlayerID>(
			json.ToSharedRef(),
			playerTurn.Get(), 0, 0);
	}

	const TSharedPtr<FPlayerID>& getPlayerTurn() { return playerTurn; }

private:
	TSharedPtr<FPlayerID> playerTurn;
};