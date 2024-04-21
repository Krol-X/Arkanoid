#include "game/brick.h"

void Brick::draw(ImGuiIO& io, ImDrawList& draw_list)
{
    Vect screen_lt = world.toScreenCoords(center - half_size);
    Vect screen_rb = world.toScreenCoords(center + half_size);
    draw_list.AddRectFilled(screen_lt, screen_rb, ImColor(156, 102, 31));
}
