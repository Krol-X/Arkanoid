#pragma once

#include "base.h"

namespace Game
{
	namespace Objects
	{
		class Ball;
		class Carriage;
		class Brick;
	}
	using Objects::Ball;
	using Objects::Carriage;
	using Objects::Brick;

	class State;

	class GamePlay
	{
	public:
		GamePlay();
		virtual ~GamePlay() = default;
		void init(State* state);

		bool isAlive();
		void setAlive(bool flag = true);

		bool isPaused();
		void setPaused(bool flag);
		bool isNextStep();

		bool isNeedReset();
		void reset();

		void step(bool immediate = false);
		void render(ImDrawList& draw_list);

		int getScore();
		void addScore(int value);

		float getLifes();
	private:
		State* state;
		Ball* ball = NULL;
		Carriage* carriage = NULL;
		std::vector<Brick*> bricks;
		std::vector<Brick*> to_remove;
		bool alive;
		bool paused;
		bool next_step;
		bool need_reset;
		int score;

		void initBall();
		void initCarriage();
		void initBricks();
		void checkCollisions();
	};
	static void render_game(State& state, ImDrawList& draw_list);
}

#include "game/objects/ball.h"
#include "game/objects/carriage.h"
#include "game/objects/brick.h"
#include "game/state.h"
