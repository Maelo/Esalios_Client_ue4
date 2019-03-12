#pragma once

#include "CoreMinimal.h"

class EFTAMap;
class FString;

class EFTAJsonParser
{
public :
	static TSharedPtr<EFTAMap> ParseMapJson(const FString& jsonName);

	static TSharedPtr<EFTAMap> ParseMapJson(TSharedPtr<FJsonObject> jsonObject);
};
