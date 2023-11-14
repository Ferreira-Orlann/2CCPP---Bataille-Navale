#pragma once

#include "internalgame.hpp"
#include "asset.hpp"
#include "raylib-cpp.hpp"

class VisualGame : public InternalGame
{
private:
	raylib::Window* window;
	std::vector<Asset*> assets;
public:
	VisualGame(Vector2 vec2, std::string title);
	~VisualGame();
	void Tick();
	void Render();
	bool End();
};