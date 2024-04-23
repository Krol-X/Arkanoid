#pragma once

#include "engine/game_object.h"

class Brick : public GameObject
{
public:
	Brick(GameWorld& world, Vect& position, Vect& size);

	bool handleCollision(GameObject& object, CollisionSide side);
	void draw(ImGuiIO& io, ImDrawList& draw_list);
private:
	const float MAX_DAMAGE = 1.0f;
	const float DAMAGE = 0.5f;

	float damage = 0.f;
};
