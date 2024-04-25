#include "game/gameplay.h"

namespace Game
{
	GamePlay::GamePlay()
		: state(NULL), alive(false), paused(false), next_step(false), score(0)
	{
	}

	void GamePlay::init(State* state)
	{
		this->state = state;
		auto level_settings = state->levelSettings();
		state->io().setContainerSize(level_settings.world_size);
		initBall();
		initCarriage();
		Brick::init(*state);
		initBricks();
	}

	bool GamePlay::isAlive()
	{
		return alive;
	}

	void GamePlay::setAlive(bool flag)
	{
		alive = flag;
	}

	bool GamePlay::isPaused()
	{
		return paused;
	}

	void GamePlay::setPaused(bool flag)
	{
		paused = flag;
	}

	bool GamePlay::isNextStep()
	{
		return next_step;
	}

	bool GamePlay::isNeedReset()
	{
		return need_reset;
	}

	void GamePlay::reset()
	{
		need_reset = true;
		setAlive(false);
	}

	static void render_game(State& state, ImDrawList& draw_list)
	{
		auto gameplay = state.gameplay();
		gameplay.render(draw_list);

		char buf[100];
		sprintf(buf, "Score: %u\nLifes: %.0f", gameplay.getScore(), gameplay.getLifes());

		state.io().drawText(draw_list, buf, Vect(0.f), ImVec4(1.f, 1.f, 1.f, 1.f), 36);
	}

	void GamePlay::render(ImDrawList& draw_list)
	{
		ball->draw(draw_list);
		carriage->draw(draw_list);
		for (Brick* brick : bricks)
		{
			brick->draw(draw_list);
		}
	}

	void GamePlay::step(bool immediate)
	{
		if (immediate)
			next_step = true;

		auto& io = state->io();
		auto& gameplay = state->gameplay();
		float elapsed_time = io.getElapsedTime();

		if (io.keyPressed(GLFW_KEY_ESCAPE))
		{
			setAlive(false);
			return;
		}

		// if (io.keyPressed(GLFW_KEY_TAB, true))
		// settings.gui_draw = !settings.gui_draw;

		state->debug().update(elapsed_time);

		// TODO: draw windows

		if (gameplay.isPaused() && !gameplay.isNextStep())
			return;

		ball->update(elapsed_time);
		carriage->update(elapsed_time);
		checkCollisions();

		state->io().tick(render_game);

		next_step = false;
	}

	int GamePlay::getScore()
	{
		return score;
	}

	void GamePlay::addScore(int value)
	{
		score += value;
	}

	float GamePlay::getLifes()
	{
		return ball->getLifes();
	}

	void GamePlay::initBall()
	{
		auto level_settings = state->levelSettings();
		Vect ball_pos = Vect(level_settings.world_size.x / 2.0f, level_settings.world_size.y / 2.0f);

		float random_angle = (40 + std::rand() % 20) * M_PI / 180.0f;
		if (std::rand() % 20 > 10)
			random_angle = random_angle + 45;

		float x_vel = level_settings.ball_speed * std::cos(random_angle);
		float y_vel = level_settings.ball_speed * std::sin(random_angle);
		Vect ball_vel = Vect(x_vel, y_vel);

		ball = new Ball(*state, ball_pos, level_settings.ball_radius, ball_vel);
	}

	void GamePlay::initCarriage()
	{
		auto level_settings = state->levelSettings();
		Vect& carriage_size = level_settings.carriage_size;
		Vect carriage_pos = Vect(level_settings.world_size.x / 2.0f, level_settings.world_size.y - carriage_size.y - 10.0f);
		carriage = new Carriage(*state, carriage_pos, carriage_size);
	}

	void GamePlay::initBricks()
	{
		auto lvl_set = state->levelSettings();
		float bricks_width = (lvl_set.world_size.x - (lvl_set.bricks_columns_count + 1.0f) * lvl_set.bricks_columns_padding) / lvl_set.bricks_columns_count;
		float bricks_height = (lvl_set.world_size.y / 3.0f - (lvl_set.bricks_rows_count + 1.0f) * lvl_set.bricks_rows_padding) / lvl_set.bricks_rows_count;

		float start_x = lvl_set.bricks_columns_padding + bricks_width / 2.0f;
		float start_y = bricks_height;

		for (int row = 0; row < lvl_set.bricks_rows_count; ++row)
		{
			for (int col = 0; col < lvl_set.bricks_columns_count; ++col)
			{
				float brick_x = start_x + col * (bricks_width + lvl_set.bricks_columns_padding);
				float brick_y = start_y + row * (bricks_height + lvl_set.bricks_rows_padding);
				Vect brick_pos(brick_x, brick_y);
				Vect brick_size(bricks_width, bricks_height);
				Brick* brick = new Brick(*state, brick_pos, brick_size);
				bricks.push_back(brick);
			}
		}
	}

	void GamePlay::checkCollisions()
	{
		std::vector<Brick*> bricks_to_remove;

		auto collsion = ball->getCollisionVector(*carriage);
		if (collsion)
		{
			ball->handleCollision(*carriage, collsion);
		}

		for (Brick* brick : bricks)
		{
			auto collsion = ball->getCollisionVector(*brick);
			if (collsion)
			{
				ball->handleCollision(*brick, collsion);
				brick->handleCollision(*ball, collsion);
				if (brick->getLifes() <= 0)
					bricks_to_remove.push_back(brick);
				break;
			}
		}

		// Delete destroyed bricks
		for (Brick* brick : bricks_to_remove)
		{
			auto it = std::find(bricks.begin(), bricks.end(), brick);
			if (it != bricks.end())
			{
				bricks.erase(it);
				delete brick;
			}
		}
	}
}