#include "engine/game_object.h"

const Vect& GameObject::getPosition() const {
	return position;
}

const Vect& GameObject::getSize() const {
	return size;
}

const Vect& GameObject::getHalfSize() const {
	return half_size;
}

const Vect& GameObject::getVelocity() const {
	return velocity;
}

float GameObject::getBounceFactor() const
{
	return bounce_factor;
}

// Алгоритм минимального вектора пересечения (Minimum Translation Vector, MTV)
CollisionSide GameObject::getCollisionVector(GameObject& object) const
{
	Vect position2 = object.position;
	Vect half_size2 = object.half_size;

	// Проверка пересечения
	if (position2.x + half_size2.x < position.x - half_size.x
		|| position.x + half_size.x < position2.x - half_size2.x
		|| position2.y + half_size2.y < position.y - half_size.y
		|| position.y + half_size.y < position2.y - half_size2.y) {
		return NONE;
	}

	// Вычисление минимального вектора пересечения
	float overlapX = std::min(position.x + half_size.x, position2.x + half_size2.x) -
		std::max(position.x - half_size.x, position2.x - half_size2.x);
	float overlapY = std::min(position.y + half_size.y, position2.y + half_size2.y) -
		std::max(position.y - half_size.y, position2.y - half_size2.y);

	// Определение стороны столкновения
	if (overlapX > overlapY) {
		return (position.y < position2.y) ? TOP_SIDE : BOTTOM_SIDE;
	}
	else {
		return (position.x < position2.x) ? LEFT_SIDE : RIGHT_SIDE;
	}
}

bool GameObject::handleCollision(GameObject& object, CollisionSide side)
{
	return false;
}

bool GameObject::update(const ImGuiIO& io, float elapsed) {
	position += velocity * elapsed;
	return false;
}

void GameObject::draw(ImGuiIO& io, ImDrawList& draw_list)
{
}
