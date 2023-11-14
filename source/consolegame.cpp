#include "consolegame.hpp"
#include <iostream>
#include <algorithm>

void ConsoleGame::Print(Player player)
{
	std::vector<Position2> vec = std::vector<Position2>();
	for (auto itboat = this->boats.begin(); itboat != this->boats.end(); itboat++)
	{
		this->ComputeBoatPos((*itboat)->GetPosition(), (*itboat)->GetSize(), (*itboat)->GetOrientation(), &vec);
	}
	for (uint8_t i = 0; i < 10; i++)
	{
		for (uint8_t j = 0; j < 10; j++)
		{	
			auto last = vec.end();
			auto it = std::find(vec.begin(), last, Position2( (uint8_t) i, (uint8_t) j ));
			if (it == last)
			{
				if (this->board[!player][((i) * 10) + j]) {
					std::cout << "O";
					continue;
				}
				std::cout << " ";
				continue;
			}
			std::cout << "X";
		}
		std::cout << std::endl;
	}
}

ConsoleGame::ConsoleGame(bool bypass)
{
	if (!bypass)
	{
		int sizes[10] = { 5,5,4,4,3,3,3,3,2,2 };
		for (int i = 0; i < 10; i++)
		{
			this->Print(i % 2 == 0);
			char x, y;
			char orientation;
			//std::cout << "Size: " << sizes[i] << std::endl;
			std::cout << "Saisir X : ";
			std::cin >> x;
			x = atoi(&x);
			x--;
			std::cout << "Saisir Y : ";
			std::cin >> y;
			y = atoi(&y);
			y--;
			std::cout << "Saisir Orientation (TOP 1, DOWN 2, RIGHT 3, LEFT 4) : ";
			std::cin >> orientation;
			orientation = atoi(&orientation);
			try {
				if (i % 2 == 0)
					this->AddBoat(sizes[i], true, (Orientation) orientation, { (uint8_t) x, (uint8_t) y });
				else
					this->AddBoat(sizes[i], false, (Orientation) orientation, { (uint8_t) x, (uint8_t) y });
			}
			catch (...)
			{
				i--;
			}
		}
	}
	
	while (true)
	{
		uint8_t x, y;
		std::cout << "Player One" << std::endl;
		this->Print(true);
		std::cout << "Saisir X : ";
		std::cin >> x;
		x--;
		std::cout << "Saisir Y : ";
		std::cin >> y;
		y--;
		InternalGame::CollisionResult r = this->Attack({ x, y }, true);
		if (r.collide)
		{
			std::cout << "Touché" << std::endl;
			if (!r.boat->IsAlive())
				std::cout << "Bâteau (size: " << r.boat->GetSize() << ")coulé" << std::endl;
		}
		else
		{
			std::cout << "Loupé" << std::endl;
		}

		std::cout << "Player Two" << std::endl;
		this->Print(false);		std::cout << "Saisir X : ";
		std::cin >> x;
		x--;
		std::cout << "Saisir Y : ";
		std::cin >> y;
		y--;
		r = this->Attack({ x, y }, true);
		if (r.collide)
		{
			std::cout << "Touché" << std::endl;
			if (!r.boat->IsAlive())
				std::cout << "Bâteau (size: " << r.boat->GetSize() << ")coulé" << std::endl;
		}
		else
		{
			std::cout << "Loupé" << std::endl;
		}
	}
}
