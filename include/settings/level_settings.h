#pragma once

#include "base.h"

namespace Settings
{
	struct LevelSettings
	{
		// World
		Vect world_size = Vect(800.0f, 600.f);
		// Ball
		float ball_radius = 10.0f;
		float ball_speed = 150.0f;
		float ball_full_life = 5.0f;
		float ball_damage = 1.0f;
		float ball_bounce_coefficient = 1.00f;
		// Carriage
		Vect carriage_size = Vect(80.0f, 20.0f);
		float carriage_speed = 0.f;
		float carriage_braking_coefficient = 0.9f;
		float carriage_bounce_coefficient = 0.95f;
		// Bricks
		int bricks_columns_count = 15;
		int bricks_rows_count = 7;
		float bricks_columns_padding = 5.0f;
		float bricks_rows_padding = 5.0f;
		float bricks_full_life = 1.0f;
		float bricks_damage = 0.5f;
		float bricks_bounce_coefficient = 1.10f;
		int brick_score = 5;
		// Debug
		float debug_draw_pos_radius = 5.0f;
		float debug_draw_normal_length = 30.0f;
		float debug_draw_timeout = 0.5f;
	};
}
