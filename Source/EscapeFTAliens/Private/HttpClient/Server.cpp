#include "Server.h"
#include "Json.h"
#include "Serialization/JsonSerializer.h"
#include "EscapeFTAliens/Public/HttpClient/Request/Request.h"

const FString AServerManager::constructUrl(TSharedPtr<HttpRequest> requestConf)
{
	FString url(host_ + requestConf->getUrlPath());

	auto paramList = requestConf->getParams();

	if (paramList.Num())
	{
		url += "?";

		for (int i = 0; i < paramList.Num(); i++) {
			TPair<FString, FString> paramPair = paramList[i];

			url += paramPair.Key + "=" + paramPair.Value;

			if (i < paramList.Num() - 1)
			{
				url += "&";
			}
		}
	}

	return url;
}


void AServerManager::sendCall(TSharedPtr<HttpRequest> requestConf)
{
	FString url(constructUrl(requestConf));

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &AServerManager::onResponseReceived, requestConf);

	Request->SetURL(url);

	if (requestConf->getType() == HttpRequest::GET)
	{
		Request->SetVerb("GET");
	}
	else
	{
		Request->SetVerb("POST");
	}
	
	for (const auto& header : requestConf->getHeaders())
	{
		Request->SetHeader(header.Key, header.Value);
	}

	if (requestConf->getType() == HttpRequest::POST && !requestConf->getContent().IsEmpty())
	{
		Request->SetContentAsString(requestConf->getContent());
	}

	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();

	requestConf->postRequestSent();
}

void AServerManager::onResponseReceived(FHttpRequestPtr Request, 
										FHttpResponsePtr Response, 
										bool bWasSuccessful, 
										TSharedPtr<HttpRequest> request)
{
	TSharedPtr<FJsonObject> JsonObject;
	if (!Response.IsValid())
	{
		return;
	}

	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	UE_LOG(LogTemp, Warning, TEXT("Response Code received : %d"), Response->GetResponseCode());

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		request->setObjectResponse(JsonObject);

		request->parseJsonResponse();
		
		request->setReceivedResponse(true);
	}
}

AServerManager::AServerManager(const FObjectInitializer & ObjectInitializer)
	: Http(&FHttpModule::Get())
	//, host_("http://127.0.0.1:5000")
	, host_("https://qxjasvc7j1.execute-api.us-east-1.amazonaws.com/Prod")
{
}

void AServerManager::BeginPlay()
{
}
