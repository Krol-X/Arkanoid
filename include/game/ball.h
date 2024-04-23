#pragma once

#include "engine/game_object.h"

class Ball : public GameObject
{
public:
	Ball(GameWorld& world, Vect& position, float radius, Vect& velocity);

	bool handleCollision(GameObject& object, CollisionSide side);
	bool update(ImGuiIO& io, float elapsed);
	void draw(ImGuiIO& io, ImDrawList& draw_list);
};
