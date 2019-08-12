#pragma once
#include "CoreMinimal.h"

#include "JsonStruct/GameStruct.h"
#include "JsonStruct/PlayerStruct.h"
#include "JsonStruct/ActionStruct.h"
#include "EscapeFTAliens/Public/HttpClient/Request/Request.h"

class PostGameRequest : public HttpRequest
{
public:
	PostGameRequest()
		: HttpRequest("/game", HttpRequest::POST, "GameRequest")
	{
		TSharedPtr<FJsonObject> root(MakeShareable(new FJsonObject));

		//TODO
		root->SetStringField("username", "yoyo");
		
		//Write jsonObject to FString
		FString OutputString;
		TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(root.ToSharedRef(), Writer);
		
		setContent(OutputString);
	}

	virtual void parseJsonResponse()
	{
		TSharedPtr<FJsonObject> json = getObjectResponse();
		game_  = MakeShareable(new FGameStruct);

		FJsonObjectConverter::JsonObjectToUStruct<FGameStruct>(
			json.ToSharedRef(),
			game_.Get(), 0, 0);
	}

	TSharedPtr<FGameStruct> getGame() { return game_; }

private:

	TSharedPtr<FGameStruct> game_;
};

class JoinGameRequest : public HttpRequest
{
public:
	JoinGameRequest()
		: HttpRequest("/join", HttpRequest::POST, "GameRequest")
	{
		TSharedPtr<FJsonObject> root(MakeShareable(new FJsonObject));

		//TODO
		root->SetStringField("username", "yoyo");

		//Write jsonObject to FString
		FString OutputString;
		TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(root.ToSharedRef(), Writer);

		setContent(OutputString);
	}

	virtual ~JoinGameRequest() {};

	virtual void parseJsonResponse() override
	{
		TSharedPtr<FJsonObject> json = getObjectResponse();
		game = MakeShareable(new FGameStruct);

		FJsonObjectConverter::JsonObjectToUStruct<FGameStruct>(
			json.ToSharedRef(),
			game.Get(), 0, 0);
	}

	TSharedPtr<FGameStruct> getGame() { return game; }

private:

	TSharedPtr<FGameStruct> game;
};

class MoveRequest : public HttpRequest
{
public:
	MoveRequest(int32 x, int32 y, FString playerID)
		: HttpRequest("/move", HttpRequest::POST, "MoveRequest")
	{
		TSharedPtr<FJsonObject> root(MakeShareable(new FJsonObject));

		//Struct to jsonObject
		FMoveRequest moveRequest{x, y, playerID};
		root = FJsonObjectConverter::UStructToJsonObject(moveRequest);

		//Write jsonObject to FString
		FString OutputString;
		TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(root.ToSharedRef(), Writer);

		setContent(OutputString);
	}

	virtual void parseJsonResponse()
	{
		TSharedPtr<FJsonObject> json = getObjectResponse();

		isValidMove_ = json->GetBoolField("isValidMove");
	}

	const bool& isValidMove() { return isValidMove_; }

private:

	bool isValidMove_;
};