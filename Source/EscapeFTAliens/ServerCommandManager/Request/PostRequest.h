#pragma once
#include "CoreMinimal.h"

#include "Utilities/JsonParser.h"

#include "ServerCommandManager/Request/Request.h"

class PostGameRequest : public HttpRequest
{
public:
	PostGameRequest()
		: HttpRequest("/game", HttpRequest::POST)
	{
		addParam(TPair<FString, FString>("username", "yoyo"));
	}

	virtual void parseJsonResponse()
	{
		TSharedPtr<FJsonObject> json = getObjectResponse();

		map = EFTAJsonParser::ParseMapJson(json);
	}

	EFTAMap* getMap() { return map; }

private:

	EFTAMap* map;

};