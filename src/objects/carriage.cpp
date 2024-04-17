#include "carriage.h"
#include <GLFW/glfw3.h>

void Carriage::update(ImGuiIO& io, float elapsed)
{
    const float DELAY_COEFFICIENT = 0.9f;

    // Input check
    if (io.KeysDown[GLFW_KEY_A] || io.KeysDown[GLFW_KEY_LEFT]) {
        velocity.x -= 15.0f;
        if (velocity.x < -200.0f)
            velocity.x = -200.0f;
    }
    else if (io.KeysDown[GLFW_KEY_D] || io.KeysDown[GLFW_KEY_RIGHT]) {
        velocity.x += 15.0f;
        if (velocity.x > 200.0f)
            velocity.x = 200.0f;
    }
    else {
        velocity.x *= DELAY_COEFFICIENT;
        if (std::abs(velocity.x) < 1.0f) {
            velocity.x = 0.0f;
        }
    }

    // Move
    GameObject::update(io, elapsed);

    // Check edges
    if (center.x < half_size.x)
    {
        center.x = half_size.x;
        velocity.x = 0;
    }
    else if (center.x > (world.getSize().x - half_size.x))
    {
        center.x = world.getSize().x - half_size.x;
        velocity.x = 0;
    }
}

void Carriage::draw(ImGuiIO& io, ImDrawList& draw_list)
{
    Vect screen_lt = world.toScreenCoords(center - half_size);
    Vect screen_rb = world.toScreenCoords(center + half_size);
    draw_list.AddRectFilled(screen_lt, screen_rb, ImColor(255, 255, 255));
}
