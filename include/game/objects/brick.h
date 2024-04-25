#pragma once

#include "engine/game_object.h"

namespace Game::Objects
{
	class Brick : public Engine::GameObject
	{
	public:
		static void init(State& state);
		Brick(State& state, Vect& position, Vect& size);
		virtual ~Brick() = default;

		float getLifes();

		void handleCollision(GameObject& object, Engine::CollisionSide side);

		void draw(ImDrawList& draw_list);
	private:
		static int audio_brick_id;
		float lifes, full_life;
		int brick_score;
	};
}
