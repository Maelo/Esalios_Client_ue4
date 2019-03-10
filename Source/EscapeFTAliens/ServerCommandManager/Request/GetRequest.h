#pragma once
#include "CoreMinimal.h"

#include "ServerCommandManager/Request/Request.h"

class GetPlayerRequest : public HttpRequest
{
public:
	GetPlayerRequest()
		: HttpRequest("/getPlayer", HttpRequest::GET, HttpRequest::NameRequest::GetPlayer)
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