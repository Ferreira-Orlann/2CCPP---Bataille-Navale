#include "internalgame.hpp"
#include <exception>
#include <iostream>

void InternalGame::ComputeBoatPos(Position2 bPos, size_t bSize, Orientation orientation, std::vector<Position2>* vec)
{

	switch (orientation)
	{
	case DOWN:
		for (uint8_t y = bPos.y; y < bPos.y + bSize; y++)
			vec->push_back({ bPos.x, y });
		break;
	case TOP:
			std::cout << "t\n";
		for (uint8_t y = bPos.y; y > bPos.y + bSize; y--) {
			vec->push_back({ bPos.x, y });
		}
		break;
	case RIGHT:
		for (uint8_t x = bPos.x; x < bPos.x + bSize; x++)
			vec->push_back({ x, bPos.y });
		break;
	case LEFT:
		for (uint8_t x = bPos.x; x > bPos.x + bSize; x--)
			vec->push_back({ x, bPos.y });
		break;
	}
};

bool InternalGame::CanPlaceBoat(size_t size, Player player, Orientation orientation, Position2 pos)
{
	std::vector<Position2> testVec = std::vector<Position2>();
	this->ComputeBoatPos(pos, size, orientation, &testVec);
	std::cout << "Size:" << testVec.size();
	for (auto tPos : testVec)
	{
		if (tPos.x >= 10 || tPos.y >= 10 || tPos.x < 0 || tPos.y < 0)
			return false;
	}
	std::vector<Position2> vec = std::vector<Position2>();
	for (auto itboat = this->boats.begin(); itboat != this->boats.end(); itboat++)
	{
		this->ComputeBoatPos((*itboat)->GetPosition(), (*itboat)->GetSize(), (*itboat)->GetOrientation(), &vec);
	}
	for (auto tPos : testVec)
	{
		for (auto pos : vec)
		{
			if (tPos == pos)
				return false;
		}
	}
	return true;
};

void InternalGame::AddBoat(size_t size, Player player, Orientation orientation, Position2 pos)
{
	if (this->boats.size() > 10)
	{
		throw std::exception("Too many boats");
	}
	if (!this->CanPlaceBoat(size, player, orientation, pos))
	{
		throw std::exception("Can't place boat");
	}
	pBoat boat = std::make_shared<Boat>(size, player, orientation, pos, (char) this->boats.size());
	this->boats.push_back(boat);
}

	
InternalGame::CollisionResult InternalGame::CheckCollision(Position2 pos, Player player) const
{
	for (auto itboat = this->boats.begin(); itboat != this->boats.end(); itboat++)
	{
		if ((*itboat)->GetOwner() != player && (*itboat)->CheckCollision(pos))
			return { true, *itboat};
	}
	return { false, nullptr};
}

void InternalGame::BoardInsert(Position2 pos, Player player)
{
	player ?
		this->board[0][(( pos.x) * 10) + pos.y] = true 
	: 
		this->board[1][(( pos.x) * 10) + pos.y] = true;
}

InternalGame::CollisionResult InternalGame::Attack(Position2 pos, Player player)
{
	if ((player && this->board[0][((pos.x) * 10) + pos.y]) || (!player && this->board[1][((pos.x) * 10) + pos.y]))
	{
		this->BoardInsert(pos, player);
		InternalGame::CollisionResult r = this->CheckCollision(pos, player);
		if (r.collide)
		{
			r.boat->IncrementHit();
			int hit = r.boat->GetHit();
			if (hit >= r.boat->GetSize())
			{
				r.boat->SetAlive(false);
			}

		}
		return r;
	}
	return { false, nullptr };
}

pBoat InternalGame::GetBoat(uint8_t id) const
{
	for (auto itboat = this->boats.begin(); itboat != this->boats.end(); itboat++)
	{
		if ((*itboat)->GetId() == id)
			return *itboat;
	}
	return { nullptr };
}

InternalGame::EndCond InternalGame::EndCompute() const
{
	uint8_t pOne = 0;
	uint8_t pTwo = 0;
	for (auto itboat = this->boats.begin(); itboat != this->boats.end(); itboat++)
	{
		if (!(*itboat)->IsAlive())
		{
			if ((*itboat)->GetOwner())
			{
				pTwo++;
				continue;
			}
			pOne++;
		}
	}
	if (pOne == 5)
	{
		return PLAYER_ONE_WIN;
	}
	else if (pTwo == 5)
	{
		return PLAYER_TWO_WIN;
	}
	return CONTINUE;
}