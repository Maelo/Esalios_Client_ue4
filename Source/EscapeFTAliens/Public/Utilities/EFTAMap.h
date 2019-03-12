#pragma once
#include "CoreMinimal.h"
#include "EFTAMap.generated.h"

UENUM(BlueprintType)
enum class EBlockType : uint8
{
	BT_SECURE 	UMETA(DisplayName = "Secure Sector"),
	BT_DANGER 	UMETA(DisplayName = "Dangerous Sector"),
	BT_HUMAN	UMETA(DisplayName = "Human Sector"),
	BT_ALIEN	UMETA(DisplayName = "Alien Sector"),
	BT_ESCAPE	UMETA(DisplayName = "Escape Sector"),
	BT_BLOCKED	UMETA(DisplayName = "Blocked Sector")
};

struct FSector
{
	FSector() {};

	FSector(const int x_, const int y_, const EBlockType type_) 
		: x(x_)
		, y(y_)
		, type(type_) 
	{};

	bool operator==(const FSector& other) const
	{
		if (getX() == other.getX() && getY() == other.getY())
		{
			return true;
		}
		return false;
	}

	EBlockType type;

	int getX() const 
	{ 
		return x; 
	}

	void setX(int val) 
	{ 
		x = val; 
	}

	int getY() const 
	{ 
		return y; 
	}

	void setY(int val) 
	{ 
		y = val; 
	}

private:
	int x;
	int y;
};

class EFTAMap
{
public:

	EFTAMap(FString name, FVector2D size) : name_(name), size_(size) {};

	const FString getName() const { return name_; };

	const TArray<FSector> getSectorList() const { return sectorList_; };

	const FVector2D getSize() const { return size_; }

	void addSector(FSector sector) { sectorList_.Add(sector); }

private:
	FString name_;

	TArray<FSector> sectorList_;

	FVector2D size_;
};