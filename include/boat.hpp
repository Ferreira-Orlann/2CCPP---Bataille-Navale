#pragma once

#include <cstddef>
#include "enums.hpp"
#include "position.hpp"
#include "player.hpp"
#include <array>

class Boat
{
private:
	size_t size;
	Player owner;
	Orientation orientation;
	Position2 pos;
	bool alive = true;
	uint8_t hit = 0;
	uint8_t id;
public:
	Boat(size_t size, bool owner, Orientation orientation, Position2 pos, char id);
	bool CheckCollision(Position2 pos) const;
	bool GetOwner() const;
	bool IsAlive() const;
	void SetAlive(bool val);
	size_t GetSize() const;
	uint8_t GetId() const;
	uint8_t GetHit() const;
	void IncrementHit();
	Orientation GetOrientation() const;
	Position2 GetPosition() const;
};