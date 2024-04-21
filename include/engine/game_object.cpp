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

// todo
std::vector<Vect> GameObject::getPoints() const {
	std::vector<Vect> points;
	points.push_back(Vect(center.x - half_size.x, center.y - half_size.y));
	points.push_back(Vect(center.x + half_size.x, center.y - half_size.y));
	points.push_back(Vect(center.x - half_size.x, center.y + half_size.y));
	points.push_back(Vect(center.x + half_size.x, center.y + half_size.y));
	return points;
}

bool GameObject::containsPoint(const Vect& point) const
{
	Vect min = center - half_size;
	Vect max = center + half_size;

	return (point.x >= min.x && point.x <= max.x) &&
		(point.y >= min.y && point.y <= max.y);
}

Vect GameObject::getCollisionVector(const Vect& point) const
{
	Vect result = Vect(0.f);

	if (point.x < center.x)
		result.x = -1.0f;
	else if (center.x < point.x)
		result.x = 1.0f;

	if (point.y < center.y)
		result.y = -1.0f;
	else if (center.y < point.y)
		result.y = 1.0f;

	return result;
}

void GameObject::handleCollision(const Vect& collision_vector)
{
	velocity *= -collision_vector;
}

void GameObject::update(const ImGuiIO& io, float elapsed) {
	center += velocity * elapsed;
}
