#pragma once

#include <vector>
#include "boat.hpp"
#include <map>
#include "position.hpp"
#include <memory>
#include "player.hpp"

typedef std::shared_ptr<Boat> pBoat;

class InternalGame
{
protected:
	std::vector<pBoat> boats = std::vector<pBoat>();
	std::vector<bool> board[2] = { std::vector<bool>(100, false), std::vector<bool>(100, false) };
	void ComputeBoatPos(Position2 bPos, size_t bSize, Orientation orientation, std::vector<Position2>* vec);
public:
	struct CollisionResult
	{
		bool collide{ false };
		pBoat boat{ nullptr };
	};
	
	enum EndCond {
		CONTINUE,
		PLAYER_ONE_WIN,
		PLAYER_TWO_WIN
	};

	bool CanPlaceBoat(size_t size, Player player, Orientation orientation, Position2 pos);
	void AddBoat(size_t size, Player player, Orientation orientation, Position2 pos);
	InternalGame::CollisionResult CheckCollision(Position2 pos, Player player) const;
	void BoardInsert(Position2 pos, Player player);
	InternalGame::CollisionResult Attack(Position2 pos, Player player);
	pBoat GetBoat(uint8_t id) const;
	InternalGame::EndCond EndCompute() const;
};