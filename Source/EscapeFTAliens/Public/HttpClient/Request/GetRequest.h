#pragma once
#include "CoreMinimal.h"
#include "JsonStruct/MapStruct.h"

#include "EscapeFTAliens/Public/HttpClient/Request/Request.h"

class GetPlayerRequest : public HttpRequest
{
public:
	GetPlayerRequest()
		: HttpRequest("/getPlayer", HttpRequest::GET, "GetPlayer")
	{}

	const FVector2D getPosition() const { return position; }

	virtual void parseJsonResponse()
	{
		TSharedPtr<FJsonObject> json = getObjectResponse();

		TSharedPtr<FJsonObject> positionObj = json->GetObjectField("PlayerPosition");

		position.X = positionObj->GetIntegerField("x");
		position.Y = positionObj->GetIntegerField("y");
	}
private:
	FVector2D position;
};

class GetMapRequest : public HttpRequest
{
public:
	GetMapRequest(FString mapName)
		: HttpRequest("/map", HttpRequest::GET, "GetMap")
		, mapName_(mapName)
	{
		addParam(TPair<FString, FString>("name", mapName));
	}

	const FString getMapName() const { return mapName_; }

	virtual void parseJsonResponse()
	{
		TSharedPtr<FJsonObject> json = getObjectResponse();
		TSharedPtr<FMapContent> JsonMap = MakeShareable(new FMapContent);

		FJsonObjectConverter::JsonObjectToUStruct<FMapContent>(
			json.ToSharedRef(),
			JsonMap.Get(), 0, 0);
	}
private:
	FString mapName_;
};