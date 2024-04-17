#pragma once

#include "base.h"
#include "imgui_impl_glfw.h"
#include "game_world.h"

class GameObject
{
public:
    GameObject(GameWorld& world, const Vect& center_position, const Vect& size)
        : world(world), center(center_position), size(size), velocity(Vect(0.f)), half_size(size / 2.0f) {}
    GameObject(GameWorld& world, const Vect& center_position, const Vect& size, const Vect& velocity)
        : world(world), center(center_position), size(size), velocity(velocity), half_size(size / 2.0f) {}
    virtual ~GameObject() = default;

    const Vect& getCenter() const;
    const Vect& getSize() const;
    const Vect& getVelocity() const;

    void update(const ImGuiIO& io, float elapsed);
    virtual void draw(ImGuiIO& io, ImDrawList& draw_list) = 0;

protected:
    GameWorld& world;
    Vect center;
    Vect size;
    Vect velocity;
    Vect half_size;
};
