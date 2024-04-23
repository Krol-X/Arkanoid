#include "game/carriage.h"
#include <GLFW/glfw3.h>
#include <string>

Carriage::Carriage(GameWorld& world, Vect& position, Vect& size)
    : GameObject(world, position, size)
{
    bounce_factor = 1.15f;
}

void Carriage::update(ImGuiIO& io, float elapsed)
{
    constexpr float DELAY_COEFFICIENT = 0.9f;
    constexpr float MIN_VELOCITY = 0.f;
    constexpr float MAX_VELOCITY = 200.0f;

    if (io.KeysDown[GLFW_KEY_A] || io.KeysDown[GLFW_KEY_LEFT]) {
        velocity.x -= 15.0f;
    }
    else if (io.KeysDown[GLFW_KEY_D] || io.KeysDown[GLFW_KEY_RIGHT]) {
        velocity.x += 15.0f;
    }
    else {
        velocity.x *= DELAY_COEFFICIENT;
    }

    if (velocity.x > MAX_VELOCITY)
    {
        velocity.x = MAX_VELOCITY;
    }
    else if (velocity.x < -MAX_VELOCITY)
    {
        velocity.x = -MAX_VELOCITY;
    }
    if (std::abs(velocity.x) < MIN_VELOCITY) {
        velocity.x = 0.0f;
    }

    // Move
    GameObject::update(io, elapsed);

    // Check edges
    if (position.x < half_size.x)
    {
        position.x = half_size.x;
        velocity.x = 0;
    }
    else if (position.x > (world.getSize().x - half_size.x))
    {
        position.x = world.getSize().x - half_size.x;
        velocity.x = 0;
    }
}

void Carriage::draw(ImGuiIO& io, ImDrawList& draw_list)
{
    Vect screen_lt = world.toScreenCoords(position - half_size);
    Vect screen_rb = world.toScreenCoords(position + half_size);
    draw_list.AddRectFilled(screen_lt, screen_rb, ImColor(255, 255, 255));
}
