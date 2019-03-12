#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Json.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Server.generated.h"

class HttpRequest;

UCLASS()
class ESCAPEFTALIENS_API AServerManager : public AActor
{
	GENERATED_BODY()

public:
	void sendCall(TSharedPtr<HttpRequest>);

	void onResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, TSharedPtr<HttpRequest>);

	AServerManager(const class FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
private:
	const FString constructUrl(TSharedPtr<HttpRequest> requestConf);

public:
	UPROPERTY(EditAnywhere)
	FString host_;

private:
	FHttpModule * Http;
};