#include "game/objects/brick.h"
#include "game/objects/object_type.h"

// todo remove
namespace Game::Objects
{
	using Game::State;
	using Engine::CollisionSide;

	int Brick::audio_brick_id = 0;
	void Brick::init(State& state)
	{
		Brick::audio_brick_id = state.audio().load("brick.wav");
	}

	Brick::Brick(State& state, Vect& position, Vect& size)
		: GameObject(state, ObjectType::BRICK, position, size)
	{
		auto level_settings = state.levelSettings();

		bounce_coefficient = level_settings.ball_bounce_coefficient;
		full_life = level_settings.bricks_full_life;
		lifes = full_life;
		brick_score = level_settings.brick_score;
	}

	float Brick::getLifes()
	{
		return lifes;
	}

	void Brick::handleCollision(GameObject& object, CollisionSide side)
	{
		lifes -= state.levelSettings().bricks_damage;
		if (lifes <= 0)
		{
			state.gameplay().addScore(brick_score);
			state.audio().play(Brick::audio_brick_id);
		}
	}

	void Brick::draw(ImDrawList& draw_list)
	{
		float lifeRatio = lifes / full_life;
		if (lifeRatio > 1.f)
			lifeRatio = 1.f;

		const ImColor baseColor = ImColor(156, 102, 31);

		ImColor color = ImColor(
			baseColor.Value.x * lifeRatio,
			baseColor.Value.y * lifeRatio,
			baseColor.Value.z * lifeRatio
		);

		Vect screen_lt = state.io().translateCoords(position - half_size);
		Vect screen_rb = state.io().translateCoords(position + half_size);
		draw_list.AddRectFilled(screen_lt, screen_rb, color);
	}
}