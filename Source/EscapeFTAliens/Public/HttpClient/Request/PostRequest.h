#pragma once
#include "CoreMinimal.h"

#include "JsonStruct/GameStruct.h"
#include "EscapeFTAliens/Public/HttpClient/Request/Request.h"

class PostGameRequest : public HttpRequest
{
public:
	PostGameRequest()
		: HttpRequest("/game", HttpRequest::POST, "GameRequest")
	{
		TSharedPtr<FJsonObject> root(MakeShareable(new FJsonObject));

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
		game  = MakeShareable(new FGameStruct);

		FJsonObjectConverter::JsonObjectToUStruct<FGameStruct>(
			json.ToSharedRef(),
			game.Get(), 0, 0);
	}

	TSharedPtr<FGameStruct> getGame() { return game; }

private:

	TSharedPtr<FGameStruct> game;
};

class JoinGameRequest : public HttpRequest
{
public:
	JoinGameRequest()
		: HttpRequest("/join", HttpRequest::POST, "GameRequest")
	{
		TSharedPtr<FJsonObject> root(MakeShareable(new FJsonObject));

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