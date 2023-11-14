#pragma once
#include <cinttypes>

struct Position2
{
	uint8_t x;
	uint8_t y;

	bool operator==(const Position2& pos) {
		return this->x == pos.x && this->y == pos.y;
	}

	Position2(uint8_t x = 0, uint8_t y = 0) : x(x), y(y) {};
 };