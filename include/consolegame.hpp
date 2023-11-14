#pragma once

#include "internalgame.hpp"

class ConsoleGame : public InternalGame
{
public:
	ConsoleGame(bool bypass);
	void Print(Player player);
};