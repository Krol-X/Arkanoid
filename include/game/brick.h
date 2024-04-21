#pragma once

#include "engine/game_object.h"

class Brick : public GameObject
{
public:
	Brick(GameWorld& world, Vect& position, Vect& size)
		: GameObject(world, position, size) {}

	bool handleCollision(GameObject& object, CollisionSide side);
	void draw(ImGuiIO& io, ImDrawList& draw_list);
};
