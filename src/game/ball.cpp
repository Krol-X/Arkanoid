#include "game/ball.h"

Ball::Ball(Vect position, float radius, Vect velocity)
	: GameObject(position, Vect(radius), velocity)
{
}

void Ball::handleEvent(const EventType event, EventParams& params)
{
	switch (event)
	{
	EVENT_UPDATE:
		// Move Ball
		GameObject::handleEvent(event, params);
		// Fix position
		update(params);
		break;
	EVENT_DRAW:
		draw(params);
		break;
	default:
		break;
	}
}

void Ball::update(EventParams& params)
{
	Vect world_size = params.parent->getSize();

	if (position.x < half_size.x)
	{
		position.x = half_size.x;
		velocity.x *= -1.0f;
	}
	else if (position.x > (world_size.x - half_size.x))
	{
		position.x = world_size.x - half_size.x;
		velocity.x *= -1.0f;
	}

	if (position.y < half_size.y)
	{
		position.y = half_size.y;
		velocity.y *= -1.0f;
	}
	else if (position.y > (world_size.y - half_size.y))
	{
		position.y = world_size.y - half_size.y;
		velocity.y *= -1.0f;
	}
}

void Ball::draw(EventParams& params)
{
	// Vect screen_pos = demo_ball_position * demo_world_to_screen;
	// float screen_radius = demo_ball_radius * demo_world_to_screen.x;
	params.draw_list.AddCircleFilled(Vect(), size.x, ImColor(100, 255, 100));
}
