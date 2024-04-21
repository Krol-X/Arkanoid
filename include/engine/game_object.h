#pragma once

#include "base.h"
#include "imgui_impl_glfw.h"
#include "game_world.h"
#include <vector>

enum CollisionSide
{
    NONE,
    LEFT_SIDE,
    RIGHT_SIDE,
    TOP_SIDE,
    BOTTOM_SIDE,
    CORNER
};

class GameObject
{
public:
    GameObject(GameWorld& world, const Vect& center_position, const Vect& size)
        : world(world), position(center_position), size(size), velocity(Vect(0.f)), half_size(size / 2.0f) {}
    GameObject(GameWorld& world, const Vect& center_position, const Vect& size, const Vect& velocity)
        : world(world), position(center_position), size(size), velocity(velocity), half_size(size / 2.0f) {}
    virtual ~GameObject() = default;

    const Vect& getPosition() const;
    const Vect& getSize() const;
    const Vect& getHalfSize() const;
    const Vect& getVelocity() const;

    CollisionSide getCollisionVector(GameObject& object) const;
    bool handleCollision(GameObject& object, CollisionSide side);

    bool update(const ImGuiIO& io, float elapsed);
    void draw(ImGuiIO& io, ImDrawList& draw_list);

protected:
    GameWorld& world;
    Vect position;
    Vect size;
    Vect velocity;
    Vect half_size;
};
