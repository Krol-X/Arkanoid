#pragma once

#include "base.h"

namespace Game { class State; }

namespace Engine
{
    using Game::State;

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
        GameObject(State& state, int type, Vect center_position, Vect size);
        GameObject(State& state, int type, Vect center_position, Vect size, Vect velocity);
        virtual ~GameObject() = default;

        const int getType() const;
        const Vect& getPosition() const;
        const Vect& getSize() const;
        const Vect& getHalfSize() const;
        const Vect& getVelocity() const;
        float getBounce—oefficient() const;

        CollisionSide getCollisionVector(GameObject& object) const;
        void handleCollision(GameObject& object, CollisionSide side);

        void update(float elapsed);
        void draw(ImDrawList& draw_list);
    protected:
        State& state;
        int type;
        Vect position;
        Vect size;
        Vect velocity;
        Vect half_size;
        float bounce_coefficient;
    };
}

#include "game/state.h"
