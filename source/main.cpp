// Bataille Navale.cpp : définit le point d'entrée de l'application.
//

#include <iostream>
#include "internalgame.hpp"
#include "enums.hpp"
#include <iostream>

#include "consolegame.hpp"

void testCollision()
{
	InternalGame game = InternalGame();
	game.AddBoat(2, true, LEFT, { 10,10 });
	std::cout << "Collide: " << game.CheckCollision({10,10}, true).collide << std::endl;
}

int main()
{
	ConsoleGame game = ConsoleGame(false);
	
}