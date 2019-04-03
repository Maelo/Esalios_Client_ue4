#pragma once
#include "CoreMinimal.h"

#include "Json.h"
#include "Public/JsonObjectConverter.h"
#include "Containers/Array.h"
#include "Misc/Timespan.h"

class HttpRequest
{
public:

	enum Type
	{
		GET,
		POST
	};

	HttpRequest(const FString& urlPath, Type type, const FString& name, int8 expiredAfter_ = 10)
		: urlPath_(urlPath)
		, type_(type)
		, receivedReponse_(false)
		, handledReponse_(false)
		, expired_(false)
		, nameResquest_(name)
		, timeCreated_(FDateTime::Now())
		, expiredAfterSec_(expiredAfter_)
	{
		headers.Add(TPair<FString, FString>(TEXT("User-Agent"), "X-UnrealEngine-Agent"));
		headers.Add(TPair<FString, FString>("Content-Type", TEXT("application/json")));
	}

	virtual ~HttpRequest() {}

	FString getUrlPath() { return urlPath_; }

	Type getType(){ return type_; }

	TSharedPtr<FJsonObject> getObjectResponse(){ return objectResponse; }

	void setObjectResponse(TSharedPtr<FJsonObject> jsonObject) { objectResponse = jsonObject; }

	bool receivedResponse() { return receivedReponse_; }

	void setReceivedResponse(bool receivedResponse) { receivedReponse_ = receivedResponse; }

	bool isHandled() { return handledReponse_; }

	void setHandledResponse(bool value) { handledReponse_ = value; }

	FDateTime getTimeCreated() { return timeCreated_; }

	FDateTime getDateTimeExpiration() { return dateTimeExpiration_; }

	const FString& getNameRequest() const { return nameResquest_; }

	bool isExpired() { return expired_; }

	void updateIsExpired(bool val) { expired_ = val; }

	void addParam(TPair<FString, FString> param) { params.Add(param); }

	TArray<TPair<FString, FString>>& getParams() { return params; }

	void addHeader(TPair<FString, FString> header) { params.Add(header); }

	TArray<TPair<FString, FString>>& getHeaders() { return headers; }

	void setContent(const FString& jsonContent) { content_ = jsonContent; }

	const FString& getContent() { return content_; }

	void postRequestSent()
	{
		dateTimeExpiration_ = FDateTime::Now() + FTimespan(0, 0, expiredAfterSec_);
	}

	virtual void parseJsonResponse() = 0;

private:
	FString urlPath_;

	Type type_;

	TSharedPtr<FJsonObject> objectResponse;

	bool receivedReponse_;

	bool handledReponse_;

	bool expired_;

	TArray<TPair<FString, FString>> params;

	TArray<TPair<FString, FString>> headers;

	FString content_;

	FString nameResquest_;

	FDateTime timeCreated_;

	FDateTime dateTimeExpiration_;

	int8 expiredAfterSec_;
};