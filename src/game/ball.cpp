#include "game/ball.h"
#include <cstdio>
#include <string>

bool Ball::handleCollision(GameObject& object, CollisionSide side)
{
	Vect position2 = object.getPosition();
	Vect half_size2 = object.getHalfSize();

	switch (side)
	{
	case CollisionSide::LEFT_SIDE:
		position.x = position2.x - half_size2.x - half_size.x;
		velocity.x = -std::abs(velocity.x);
		return true;
	case CollisionSide::RIGHT_SIDE:
		position.x = position2.x + half_size2.x + half_size.x;
		velocity.x = std::abs(velocity.x);
		return true;
	case CollisionSide::TOP_SIDE:
		position.y = position2.y - half_size2.y - half_size.y;
		velocity.y = -std::abs(velocity.y);
		return true;
	case CollisionSide::BOTTOM_SIDE:
		position.y = position2.y + half_size2.y + half_size.y;
		velocity.y = std::abs(velocity.y);
		return true;
	case CollisionSide::CORNER:
		velocity.x = -velocity.x;
		velocity.y = -velocity.y;
		return true;
	default:
		break;
	}
	return false;
}

bool Ball::update(ImGuiIO& io, float elapsed)
{
	bool result = false;
	Vect world_size = world.getSize();

	GameObject::update(io, elapsed);

	if (position.x < half_size.x)
	{
		position.x = half_size.x;
		velocity.x *= -1.0f;
		result = true;
	}
	else if (position.x > (world_size.x - half_size.x))
	{
		position.x = world_size.x - half_size.x;
		velocity.x *= -1.0f;
		result = true;
	}

	if (position.y < half_size.y)
	{
		position.y = half_size.y;
		velocity.y *= -1.0f;
		result = true;
	}
	else if (position.y > (world_size.y - half_size.y))
	{
		position.y = world_size.y - half_size.y;
		velocity.y *= -1.0f;
		world.subLife();
		result = true;
	}
	return result;
}

void Ball::draw(ImGuiIO& io, ImDrawList& draw_list)
{
	Vect p_min = world.toScreenCoords(position - half_size);
	Vect p_max = world.toScreenCoords(position + half_size);
	draw_list.AddRectFilled(p_min, p_max, ImColor(255, 150, 50));
}
