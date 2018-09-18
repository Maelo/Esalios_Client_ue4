#pragma once
#include <assert.h>
#include <math.h>
#include <vector>

class HexCoord
{
private:
	int x_, y_;

public:
	//HexCoord(int x, int y) : x_(x), y_(y) {};
	HexCoord() {};

	void setx(int x) { x_ = x; }
	void sety(int y) { x_ = y; }

	const int getx() const { return x_; }
	const int gety() const { return y_; }
};


inline bool operator==(const HexCoord& a, const HexCoord& b)
{
	return a.getx() == b.getx() && a.gety() == b.gety();
}

inline bool operator!=(const HexCoord& a, const HexCoord& b)
{
	return !(a == b);
}

HexCoord hex_add(const HexCoord& a, const HexCoord& b)
{
	return HexCoord(a.getx() + b.getx(), a.gety() + b.gety());
}

HexCoord hex_substract(const HexCoord& a, const HexCoord& b)
{
	return HexCoord(a.getx() - b.getx(), a.gety() - b.gety());
}

HexCoord hex_multiply(const HexCoord& a, int k)
{
	return HexCoord(a.getx() * k, a.gety() * k);
}

int hex_length(const HexCoord& hex)
{
	return int( (abs(hex.getx()) + abs(hex.gety())) / 2);
}

int hex_distance(const HexCoord& a, const HexCoord& b)
{
	return hex_length(hex_substract(a, b));
}

const std::vector<HexCoord> hex_directions = {
	HexCoord(+1, 0), HexCoord(+1, -1), HexCoord(0, -1),
	HexCoord(-1, 0), HexCoord(-1, +1), HexCoord(0, +1) };

HexCoord hex_direction(int direction)
{
	assert(0 <= direction && direction < 6);
	return hex_directions[direction];
}

HexCoord hex_neighbor(const HexCoord& hex, int direction)
{
	return hex_add(hex, hex_directions[direction]);
}



