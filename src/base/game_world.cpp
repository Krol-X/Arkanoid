#include "game_world.h"

void GameWorld::update(ImGuiIO& io, float elapsed)
{
	world_to_screen = Vect(io.DisplaySize.x / size.x, io.DisplaySize.y / size.y);
}

float GameWorld::toScreenCoords(float position)
{
	return position * world_to_screen.x;
}

Vect GameWorld::toScreenCoords(Vect position)
{
	return position * world_to_screen;
}
