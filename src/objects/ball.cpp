#include "ball.h"

void Ball::update(ImGuiIO& io, float elapsed)
{
    Vect world_size = world.getSize();

    GameObject::update(io, elapsed);

    if (center.x < half_size.x)
    {
        center.x = half_size.x;
        velocity.x *= -1.0f;
    }
    else if (center.x > (world_size.x - half_size.x))
    {
        center.x = world_size.x - half_size.x;
        velocity.x *= -1.0f;
    }

    if (center.y < half_size.y)
    {
        center.y = half_size.y;
        velocity.y *= -1.0f;
    }
    else if (center.y > (world_size.y - half_size.y))
    {
        center.y = world_size.y - half_size.y;
        velocity.y *= -1.0f;
    }
}

void Ball::draw(ImGuiIO& io, ImDrawList& draw_list)
{
    Vect p_min = world.toScreenCoords(center - half_size);
    Vect p_max = world.toScreenCoords(center + half_size);
    draw_list.AddRectFilled(p_min, p_max, ImColor(255, 150, 50));
}

// For circle
//bool Ball::containsPoint(const Vect& point) const
//{
//    Vect distance = point - center;
//    float sqrDistance = distance.x * distance.x + distance.y * distance.y;
//    float sqrRadius = radius * radius;
//    return sqrDistance <= sqrRadius;
//}
