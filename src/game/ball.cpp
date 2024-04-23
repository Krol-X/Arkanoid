#include "game/ball.h"
#include <cstdio>
#include <string>
#include <cmath>

Ball::Ball(GameWorld& world, Vect& position, float radius, Vect& velocity)
	: GameObject(world, position, Vect(radius * 2.0f), velocity) {}

constexpr float MIN_VELOCITY = 10.0f;
constexpr float MAX_VELOCITY = 250.0f;

bool Ball::handleCollision(GameObject& object, CollisionSide side)
{
	Vect position2 = object.getPosition();
	Vect half_size2 = object.getHalfSize();
	float factor = object.getBounceFactor();

	switch (side)
	{
	case CollisionSide::LEFT_SIDE:
		position.x = position2.x - half_size2.x - half_size.x;
		velocity.x = -std::abs(velocity.x * factor);
		break;
	case CollisionSide::RIGHT_SIDE:
		position.x = position2.x + half_size2.x + half_size.x;
		velocity.x = std::abs(velocity.x * factor);
		break;
	case CollisionSide::TOP_SIDE:
		position.y = position2.y - half_size2.y - half_size.y;
		velocity.y = -std::abs(velocity.y * factor);
		break;
	case CollisionSide::BOTTOM_SIDE:
		position.y = position2.y + half_size2.y + half_size.y;
		velocity.y = std::abs(velocity.y * factor);
		break;
	case CollisionSide::CORNER:
		velocity.x = -(velocity.x * factor);
		velocity.y = -(velocity.y * factor);
		break;
	default:
		return false;
	}

	if (std::abs(velocity.x) > MAX_VELOCITY)
		velocity.x = std::copysign(MAX_VELOCITY, velocity.x);
	if (std::abs(velocity.y) > MAX_VELOCITY)
		velocity.y = std::copysign(MAX_VELOCITY, velocity.y);

	if (std::abs(velocity.x) < MIN_VELOCITY)
		velocity.x = std::copysign(MIN_VELOCITY, velocity.x);
	if (std::abs(velocity.y) < MIN_VELOCITY)
		velocity.y = std::copysign(MIN_VELOCITY, velocity.y);

	return true;
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
	float lifeRatio = (float)world.getLifes() / (float)(world.MAX_LIFES + 2);
	const ImColor baseColor = ImColor(255, 255, 0);

	ImColor color = ImColor(
		baseColor.Value.x * lifeRatio,
		baseColor.Value.y * lifeRatio,
		baseColor.Value.z * lifeRatio
	);

	Vect p_min = world.toScreenCoords(position - half_size);
	Vect p_max = world.toScreenCoords(position + half_size);
	draw_list.AddRectFilled(p_min, p_max, color);
}
