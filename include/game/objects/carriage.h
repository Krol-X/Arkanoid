#pragma once

#include "engine/game_object.h"

namespace Game::Objects
{
	class Carriage : public Engine::GameObject
	{
	public:
		Carriage(State& state, Vect& position, Vect& size);
		virtual ~Carriage() = default;

		void update(float elapsed);
		void draw(ImDrawList& draw_list);
	};
}
