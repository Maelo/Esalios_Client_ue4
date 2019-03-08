#pragma once
#include "CoreMinimal.h"

#include "Json.h"
#include "Containers/Array.h"

class HttpRequest
{
public:

	enum type
	{
		GET,
		POST
	};

	HttpRequest(FString urlPath, type type)
		: urlPath_(urlPath)
		, type_(type)
		, receivedReponse_(false)
		, handledReponse_(false)
	{}

	FString getUrlPath() { return urlPath_; }

	type getType(){ return type_; }

	TSharedPtr<FJsonObject> getObjectResponse(){ return objectResponse; };

	void setObjectResponse(TSharedPtr<FJsonObject> jsonObject) 
	{ 
		objectResponse = jsonObject; 
	};

	bool receivedResponse() { return receivedReponse_; }

	void setReceivedResponse(bool receivedResponse) { receivedReponse_ = receivedResponse; }

	bool isHandled() { return handledReponse_; }

	void setHandledResponse(bool value) { handledReponse_ = value; }

	void addParam(TPair<FString, FString> param) { params.Add(param); }

	TArray<TPair<FString, FString>>& getParams() { return params; }

	virtual void parseJsonResponse() {};

private:
	FString urlPath_;

	type type_;

	TSharedPtr<FJsonObject> objectResponse;

	bool receivedReponse_;

	bool handledReponse_;

	TArray<TPair<FString, FString>> params;
};