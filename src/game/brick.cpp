#include "game/brick.h"

Brick::Brick(GameWorld& world, Vect& position, Vect& size)
    : GameObject(world, position, size)
{
    bounce_factor = 1.15f;
}

bool Brick::handleCollision(GameObject& object, CollisionSide side)
{
    damage += DAMAGE;

    if (damage >= MAX_DAMAGE)
    {
        world.addScore(5);
        return true;
    }
    return false;
}

void Brick::draw(ImGuiIO& io, ImDrawList& draw_list)
{
    float damageRatio = (MAX_DAMAGE - damage) / MAX_DAMAGE;

    const ImColor baseColor = ImColor(156, 102, 31);

    ImColor color = ImColor(
        baseColor.Value.x * damageRatio,
        baseColor.Value.y * damageRatio,
        baseColor.Value.z * damageRatio
    );

    Vect screen_lt = world.toScreenCoords(position - half_size);
    Vect screen_rb = world.toScreenCoords(position + half_size);
    draw_list.AddRectFilled(screen_lt, screen_rb, color);
}
