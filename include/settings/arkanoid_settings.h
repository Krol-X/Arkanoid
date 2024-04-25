#pragma once

#include "base.h"

namespace Settings
{
	struct ArkanoidSettings
	{
		// Ball
		static inline const Vect ball_radius_limits = Vect(5.0f, 20.0f);
		static inline const Vect ball_speed_limits = Vect(1.0f, 300.0f);
		static inline const Vect ball_full_life_limits = Vect(1.0f, 10.0f);
		static inline const Vect ball_damage_limits = Vect(0.25f, 5.0f);
		// Carriage
		static inline const Vect carriage_width_limits = Vect(50.0f, 100.0f);
		static inline const Vect carriage_height_limits = Vect(10.0f, 50.0f);
		static inline const Vect carriage_speed_limits = Vect(0.0f, 250.0f);
		// Bricks
		static constexpr int bricks_columns_min = 10;
		static constexpr int bricks_columns_max = 30;
		static constexpr int bricks_rows_min = 3;
		static constexpr int bricks_rows_max = 10;
		static inline const Vect bricks_cols_padding_limits = Vect(5.0f, 50.f);
		static inline const Vect bricks_rows_padding_limits = Vect(5.0f, 50.f);
	};
}
