#pragma once

#include "engine/game_object.h"

namespace Game::Objects
{
	class Ball : public Engine::GameObject
	{
	public:
		Ball(State& state, Vect& position, float radius, Vect& velocity);
		virtual ~Ball() = default;

		float getLifes();

		void handleCollision(GameObject& object, Engine::CollisionSide side);

		void update(float elapsed);
		void draw(ImDrawList& draw_list);
	private:
		float lifes, full_life;
		int audio_bounce_id;
		int audio_brick_id;
		int audio_damage_id;
	};
}
