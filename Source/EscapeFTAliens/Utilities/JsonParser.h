#pragma once

#include "CoreMinimal.h"

class EFTAMap;
class FString;

class EFTAJsonParser
{
public :
	static EFTAMap* ParseMapJson(const FString& jsonName);

	static EFTAMap* ParseMapJson(TSharedPtr<FJsonObject> jsonObject);
};
