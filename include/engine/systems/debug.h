#pragma once

#include "base.h"

namespace Game { class State; }

namespace Engine::Systems
{
	using Game::State;

	class Debug {
	public:
		struct Hit {
			Vect screen_pos;
			Vect normal;
			float time = 0.0f;
		};

		Debug();
		void init(State* state);
		~Debug();

		void addHit(const Vect& position, const Vect& normal);
		void update(float elapsed);

		const std::vector<Hit>& getHits() const;
		int getFps() const;
	private:
		State* state;
		std::vector<Hit> hits;
		float elapsed_total;
		int frame_count;
		int fps;
	};
}

#include "game/state.h"
