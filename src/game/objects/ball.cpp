#include "game/objects/ball.h"
#include "game/objects/object_type.h"
#include <cstdio>
#include <string>
#include <cmath>

// TODO: reset
namespace Game::Objects
{
	using Game::State;
	using Engine::CollisionSide;

	Ball::Ball(State& state, Vect& position, float radius, Vect& velocity)
		: Engine::GameObject(state, ObjectType::BALL, position, Vect(radius * 2.0f), velocity)
	{
		full_life = state.levelSettings().ball_full_life;
		lifes = full_life;
		audio_bounce_id = state.audio().load("bounce.wav");
		audio_damage_id = state.audio().load("damage.wav");
	}

	float Ball::getLifes()
	{
		return lifes;
	}

	void Ball::handleCollision(GameObject& object, CollisionSide side)
	{
		Vect position2 = object.getPosition();
		Vect half_size2 = object.getHalfSize();
		Vect old_position = position;
		Vect normal = Vect(0.f);
		float bounce_coef = object.getBounceÑoefficient();

		switch (side)
		{
		case CollisionSide::LEFT_SIDE:
			position.x = position2.x - half_size2.x - half_size.x;
			velocity.x = -std::abs(velocity.x * bounce_coef);
			normal.x = std::copysignf(1.f, velocity.x);
			break;
		case CollisionSide::RIGHT_SIDE:
			position.x = position2.x + half_size2.x + half_size.x;
			velocity.x = std::abs(velocity.x * bounce_coef);
			normal.x = std::copysignf(1.f, velocity.x);
			break;
		case CollisionSide::TOP_SIDE:
			position.y = position2.y - half_size2.y - half_size.y;
			velocity.y = -std::abs(velocity.y * bounce_coef);
			normal.y = std::copysignf(1.f, velocity.y);
			break;
		case CollisionSide::BOTTOM_SIDE:
			position.y = position2.y + half_size2.y + half_size.y;
			velocity.y = std::abs(velocity.y * bounce_coef);
			normal.y = std::copysignf(1.f, velocity.y);
			break;
		case CollisionSide::CORNER:
			velocity.x = -(velocity.x * bounce_coef);
			velocity.y = -(velocity.y * bounce_coef);
			normal.x = std::copysignf(1.f, velocity.x);
			normal.y = std::copysignf(1.f, velocity.y);
			break;
		default:
			return;
		}

		Vect speed_limits = state.arkanoidSettings().ball_speed_limits;
		float min_speed = speed_limits.x;
		float max_speed = speed_limits.y;

		if (std::abs(velocity.x) > max_speed)
			velocity.x = std::copysign(max_speed, velocity.x);
		if (std::abs(velocity.y) > max_speed)
			velocity.y = std::copysign(max_speed, velocity.y);

		if (std::abs(velocity.x) < min_speed)
			velocity.x = std::copysign(min_speed, velocity.x);
		if (std::abs(velocity.y) < min_speed)
			velocity.y = std::copysign(min_speed, velocity.y);

		auto object_type = object.getType();
		if (object_type == ObjectType::BRICK)
		{
			if (((Brick&)object).getLifes() > 0.f)
				state.audio().play(audio_bounce_id);
		}
		else {
			state.audio().play(audio_bounce_id);
		}

		state.debug().addHit(old_position, normal);
	}

	void Ball::update(float elapsed)
	{
		bool collision = false;
		int audio_id = audio_bounce_id;

		Vect world_size = state.levelSettings().world_size;
		Vect old_position = position;
		Vect normal = Vect(0.f);

		GameObject::update(elapsed);

		if (position.x < half_size.x)
		{
			position.x = half_size.x;
			velocity.x *= -1.0f;
			normal.x = std::copysignf(1.f, velocity.x);
			collision = true;
		}
		else if (position.x > (world_size.x - half_size.x))
		{
			position.x = world_size.x - half_size.x;
			velocity.x *= -1.0f;
			normal.x = std::copysignf(1.f, velocity.x);
			collision = true;
		}

		if (position.y < half_size.y)
		{
			position.y = half_size.y;
			velocity.y *= -1.0f;
			normal.y = std::copysignf(1.f, velocity.y);
			collision = true;
		}
		else if (position.y > (world_size.y - half_size.y))
		{
			position.y = world_size.y - half_size.y;
			velocity.y *= -1.0f;
			normal.y = std::copysignf(1.f, velocity.y);
			lifes -= state.levelSettings().ball_damage;
			if (lifes < 0)
				state.gameplay().reset();
			audio_id = audio_damage_id;
			collision = true;
		}

		if (collision) {
			state.debug().addHit(old_position, normal);
			state.audio().play(audio_id);
		}
	}

	void Ball::draw(ImDrawList& draw_list)
	{
		float lifeRatio = lifes / full_life;
		if (lifeRatio > 1.f)
			lifeRatio = 1.f;
		const ImColor baseColor = ImColor(255, 255, 0);

		ImColor color = ImColor(
			baseColor.Value.x * lifeRatio,
			baseColor.Value.y * lifeRatio,
			baseColor.Value.z * lifeRatio
		);

		Vect pos = state.io().translateCoords(position);
		float radius = state.io().translateCoords(half_size).x;
		draw_list.AddCircleFilled(pos, radius, color);
	}
}