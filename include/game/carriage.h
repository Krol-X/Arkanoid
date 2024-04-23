#pragma once

#include "engine/game_object.h"

class Carriage : public GameObject
{
public:
	Carriage(GameWorld& world, Vect& position, Vect& size);

	void update(ImGuiIO& io, float elapsed);
	void draw(ImGuiIO& io, ImDrawList& draw_list);
};
