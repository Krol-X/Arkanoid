#include "ball.h"

void Ball::update(ImGuiIO& io, float elapsed)
{
	position += velocity * elapsed;

	if (position.x < radius)
	{
		position.x += (radius - position.x) * 2.0f;
		velocity.x *= -1.0f;
	}
	else if (position.x > (world.size.x - radius))
	{
		position.x -= (position.x - (world.size.x - radius)) * 2.0f;
		velocity.x *= -1.0f;
	}

	if (position.y < radius)
	{
		position.y += (radius - position.y) * 2.0f;
		velocity.y *= -1.0f;
	}
	else if (position.y > (world.size.y - radius))
	{
		position.y -= (position.y - (world.size.y - radius)) * 2.0f;
		velocity.y *= -1.0f;
	}
}


void Ball::draw(ImGuiIO& io, ImDrawList& draw_list)
{
	Vect screen_position = world.toScreenCoords(position);
	float screen_radius = world.toScreenCoords(radius);
	draw_list.AddCircleFilled(screen_position, screen_radius, ImColor(100, 255, 100));
}
