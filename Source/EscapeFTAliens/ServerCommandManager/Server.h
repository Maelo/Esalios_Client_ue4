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

	UPROPERTY()
	FString host_;

	FHttpModule * Http;

public:
	void sendCall(TSharedPtr<HttpRequest>);

	void onResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, TSharedPtr<HttpRequest>);
	void GetPlayers();

	AServerManager(const class FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
};