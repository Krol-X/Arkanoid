#include "game/brick.h"

Brick::Brick(GameWorld& world, Vect& position, Vect& size)
    : GameObject(world, position, size)
{
    bounce_factor = 1.15f;
}

bool Brick::handleCollision(GameObject& object, CollisionSide side)
{
    world.addScore(5);
    return false;
}

void Brick::draw(ImGuiIO& io, ImDrawList& draw_list)
{
    Vect screen_lt = world.toScreenCoords(position - half_size);
    Vect screen_rb = world.toScreenCoords(position + half_size);
    draw_list.AddRectFilled(screen_lt, screen_rb, ImColor(156, 102, 31));
}
