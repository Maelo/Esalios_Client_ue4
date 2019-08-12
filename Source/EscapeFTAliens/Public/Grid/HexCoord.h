#pragma once
#include <assert.h>
#include <math.h>
#include <vector>
#include "Containers/Map.h"

class HexCoord
{


public:

	HexCoord(int x, int y) : x_(x), y_(y) {};

	HexCoord(TPair<int, int> coord) : x_(coord.Key), y_(coord.Value) {};

	HexCoord() {};

	void setCoord(TPair<int, int> coord) { x_ = coord.Key; y_ = coord.Value; }

	void setx(int x) { x_ = x; }

	void sety(int y) { x_ = y; }

	const TPair<int, int> getCoord() const { return TPair<int, int>(x_, y_); }

	const int getx() const { return x_; }

	const int gety() const { return y_; }

	HexCoord operator-(const HexCoord& other)
	{
		return HexCoord(x_ - other.x_, y_ - other.y_);
	}

	HexCoord operator+(const HexCoord& other)
	{
		return HexCoord(x_ + other.x_, y_ + other.y_);
	}

private:
	int x_, y_;
};

const std::vector<HexCoord> HEX_DIRECTIONS = {
	HexCoord(+1, 0), HexCoord(+1, -1), HexCoord(0, -1),
	HexCoord(-1, 0), HexCoord(-1, +1), HexCoord(0, +1)
};


