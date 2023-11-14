#include "visualgame.hpp"
#include "raylib-cpp.hpp"
#include <memory>

VisualGame::VisualGame(Vector2 vec2, std::string title)
{
	this->window = new raylib::Window(vec2.x, vec2.y, title);
	this->window->SetTargetFPS(60);
}

VisualGame::~VisualGame()
{
	delete this->window;
}

bool VisualGame::End()
{
	return false;
}

void VisualGame::Tick()
{

}

void VisualGame::Render()
{
	this->window->BeginDrawing();
	this->window->ClearBackground(RAYWHITE);
	this->window->DrawFPS();
	this->window->EndDrawing();
}