#pragma once

#include "../base/game_object.h"

class Carriage : public GameObject
{
public:
	Carriage(GameWorld& world, Vect& position, Vect& size)
		: GameObject(world, position, size) {}

	void update(ImGuiIO& io, float elapsed);
	void draw(ImGuiIO& io, ImDrawList& draw_list);
};
