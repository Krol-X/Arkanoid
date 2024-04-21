#include "game/ball.h"
#include <cstdio>
#include <string>

void Ball::handleCollision(GameObject& object, CollisionSide side)
{
    Vect position2 = object.getPosition();
    Vect half_size2 = object.getHalfSize();

    switch (side)
    {
    case CollisionSide::LEFT_SIDE:
        printf("LEFT_SIDE\n");
        position.x = position2.x - half_size2.x - half_size.x;
        velocity.x = -std::abs(velocity.x);
        break;
    case CollisionSide::RIGHT_SIDE:
        printf("RIGHT_SIDE\n");
        position.x = position2.x + half_size2.x + half_size.x;
        velocity.x = std::abs(velocity.x);
        break;
    case CollisionSide::TOP_SIDE:
        printf("TOP_SIDE\n");
        position.y = position2.y - half_size2.y - half_size.y;
        velocity.y = -std::abs(velocity.y);
        break;
    case CollisionSide::BOTTOM_SIDE:
        printf("BOTTOM_SIDE\n");
        position.y = position2.y + half_size2.y + half_size.y;
        velocity.y = std::abs(velocity.y);
        break;
    case CollisionSide::CORNER:
        printf("CORNER\n");
        velocity.x = -velocity.x;
        velocity.y = -velocity.y;
        break;
    default:
        break;
    }
}

void Ball::update(ImGuiIO& io, float elapsed)
{
    Vect world_size = world.getSize();

    GameObject::update(io, elapsed);

    if (position.x < half_size.x)
    {
        position.x = half_size.x;
        velocity.x *= -1.0f;
    }
    else if (position.x > (world_size.x - half_size.x))
    {
        position.x = world_size.x - half_size.x;
        velocity.x *= -1.0f;
    }

    if (position.y < half_size.y)
    {
        position.y = half_size.y;
        velocity.y *= -1.0f;
    }
    else if (position.y > (world_size.y - half_size.y))
    {
        position.y = world_size.y - half_size.y;
        velocity.y *= -1.0f;
    }
}

void Ball::draw(ImGuiIO& io, ImDrawList& draw_list)
{
    Vect p_min = world.toScreenCoords(position - half_size);
    Vect p_max = world.toScreenCoords(position + half_size);
    draw_list.AddRectFilled(p_min, p_max, ImColor(255, 150, 50));

    ImVec2 textPos(10, 10); // Позиция текста на экране
    ImU32 textColor = ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

 /*   char textBuffer[200];
    sprintf(textBuffer, "Coordinates: (%.2f, %.2f)\nVelocity: (%.2f, %.2f)",
        position.x, position.y, velocity.x, velocity.y);
    std::string textString(textBuffer);

    draw_list.AddText(ImGui::GetIO().Fonts->Fonts[0], 16.0f, textPos, textColor, textString.c_str());*/
}
