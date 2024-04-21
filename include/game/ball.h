#pragma once

#include "engine/game_object.h"

class Ball : public GameObject
{
public:
	Ball::Ball(GameWorld& world, Vect& position, float radius, Vect& velocity)
		: GameObject(world, position, Vect(radius * 2.0f), velocity) {}

	bool handleCollision(GameObject& object, CollisionSide side);
	void update(ImGuiIO& io, float elapsed);
	void draw(ImGuiIO& io, ImDrawList& draw_list);
};
