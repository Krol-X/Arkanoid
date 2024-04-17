#include "game_world.h"

GameWorld::GameWorld(Vect size)
{
	this->size = size;
}

Vect GameWorld::getSize()
{
	return size;
}

void GameWorld::update(ImGuiIO& io, float elapsed)
{
	coords_to_screen = Vect(io.DisplaySize.x / size.x, io.DisplaySize.y / size.y);
}

float GameWorld::toScreenCoords(float position)
{
	return position * coords_to_screen.x;
}

Vect GameWorld::toScreenCoords(Vect position)
{
	return position * coords_to_screen;
}
