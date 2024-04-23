#pragma once
#include "base.h"

class ArkanoidSettings
{
public:
    static constexpr int bricks_columns_min = 10;
    static constexpr int bricks_columns_max = 30;
    static constexpr int bricks_rows_min = 3;
    static constexpr int bricks_rows_max = 10;

    static constexpr float bricks_columns_padding_min = 5.0f;
    static constexpr float bricks_columns_padding_max = 20.0f;
    static constexpr float bricks_rows_padding_min = 5.0f;
    static constexpr float bricks_rows_padding_max = 20.0f;

    static constexpr float ball_radius_min = 5.0f;
    static constexpr float ball_radius_max = 50.0f;
    static constexpr float ball_speed_min = 1.0f;
    static constexpr float ball_speed_max = 1000.0f;

    static constexpr float carriage_width_min = 50.0f;

    Vect world_size = Vect(800.0f, 600.f);

    int bricks_columns_count = 15;
    int bricks_rows_count = 7;

    float bricks_columns_padding = 5.0f;
    float bricks_rows_padding = 5.0f;

    float ball_radius = 10.0f;
    float ball_speed = 150.0f;

    Vect carriage_size = Vect(100.0f, 20.0f);
    float carriage_width = 50.0f;

    float debug_draw_pos_radius = 5.0f;
    float debug_draw_normal_length = 30.0f;
    float debug_draw_timeout = 0.5f;

    bool debug_draw = false;
    bool gui_draw = false;
};
