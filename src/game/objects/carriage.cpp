#include "game/objects/carriage.h"
#include "game/objects/object_type.h"
#include <GLFW/glfw3.h>
#include <string>

namespace Game::Objects
{
	using Game::State;

	Carriage::Carriage(State& state, Vect& position, Vect& size)
		: GameObject(state, ObjectType::CARRIAGE, position, size)
	{
		bounce_coefficient = state.levelSettings().carriage_bounce_coefficient;
	}

	void Carriage::update(float elapsed)
	{
		auto& level_settings = state.levelSettings();
		float world_width = level_settings.world_size.x;

		if (state.io().keyPressed(GLFW_KEY_A) || state.io().keyPressed(GLFW_KEY_LEFT)) {
			velocity.x -= 15.0f;
		}
		else if (state.io().keyPressed(GLFW_KEY_D) || state.io().keyPressed(GLFW_KEY_RIGHT)) {
			velocity.x += 15.0f;
		}
		else {
			velocity.x *= level_settings.carriage_braking_coefficient;
		}

		Vect speed_limits = state.arkanoidSettings().ball_speed_limits;
		float min_speed = speed_limits.x;
		float max_speed = speed_limits.y;

		if (velocity.x > max_speed)
		{
			velocity.x = max_speed;
		}
		else if (velocity.x < -max_speed)
		{
			velocity.x = -max_speed;
		}
		if (std::abs(velocity.x) < min_speed)
		{
			velocity.x = min_speed;
		}

		// Move
		GameObject::update(elapsed);

		// Check edges
		if (position.x < half_size.x)
		{
			position.x = half_size.x;
			velocity.x = 0;
		}
		else if (position.x > (world_width - half_size.x))
		{
			position.x = world_width - half_size.x;
			velocity.x = 0;
		}
	}

	void Carriage::draw(ImDrawList& draw_list)
	{
		const ImColor baseColor = ImColor(150, 150, 255);

		Vect screen_lt = state.io().translateCoords(position - half_size);
		Vect screen_rb = state.io().translateCoords(position + half_size);
		draw_list.AddRectFilled(screen_lt, screen_rb, baseColor);
	}
}