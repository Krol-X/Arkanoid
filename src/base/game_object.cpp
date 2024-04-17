#include "game_object.h"

const Vect& GameObject::getCenter() const {
    return center;
}

const Vect& GameObject::getSize() const {
    return size;
}

const Vect& GameObject::getVelocity() const {
    return velocity;
}

void GameObject::update(const ImGuiIO& io, float elapsed) {
    center += velocity * elapsed;
}
