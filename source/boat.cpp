#include "boat.hpp"

Boat::Boat(size_t size, bool owner, Orientation orientation, Position2 pos, char id) : size(size), owner(owner), orientation(orientation), pos(pos), id(id) {};

bool Boat::CheckCollision(Position2 pos) const
{	
	switch (this->orientation)
	{
	case DOWN:
		if (pos.x == this->pos.x && pos.y >= this->pos.y && pos.y <= this->pos.y + (this->size - 1))
			return true;
	case TOP:
		if (pos.x == this->pos.y && pos.y <= this->pos.y && pos.y >= this->pos.y -(this->size - 1))
			return true;
	case RIGHT:
		if (pos.y == this->pos.y && pos.x >= this->pos.x && pos.x <= this->pos.x + (this->size - 1))
			return true;
	case LEFT:
		if (pos.y == this->pos.y && pos.x <= this->pos.x && pos.x >= this->pos.x - (this->size - 1))
			return true;	
	}
	return false;
}

bool Boat::GetOwner() const
{
	return this->owner;
}

bool Boat::IsAlive() const
{
	return this->alive;
}

void Boat::SetAlive(bool val)
{
	this->alive = val;	
}

size_t Boat::GetSize() const
{
	return this->size;
}

uint8_t Boat::GetId() const
{
	return this->id;
}

uint8_t Boat::GetHit() const
{
	return this->hit;
}

void Boat::IncrementHit()
{
	this->hit++;
}

Orientation Boat::GetOrientation() const
{
	return this->orientation;
}

Position2 Boat::GetPosition() const
{
	return this->pos;
}
