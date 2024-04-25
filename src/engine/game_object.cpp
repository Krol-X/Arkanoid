#include "engine/game_object.h"

namespace Engine
{
	GameObject::GameObject(State& state, int type, Vect center_position, Vect size)
		: state(state), type(type), position(center_position), size(size), velocity(Vect(0.f)),
		half_size(size / 2.0f), bounce_coefficient(1.00f) {}
	GameObject::GameObject(State& state, int type, Vect center_position, Vect size, Vect velocity)
		: state(state), type(type), position(center_position), size(size), velocity(velocity),
		half_size(size / 2.0f), bounce_coefficient(1.00f) {}

	const int GameObject::getType() const
	{
		return type;
	}

	const Vect& GameObject::getPosition() const
	{
		return position;
	}

	const Vect& GameObject::getSize() const
	{
		return size;
	}

	const Vect& GameObject::getHalfSize() const
	{
		return half_size;
	}

	const Vect& GameObject::getVelocity() const
	{
		return velocity;
	}

	float GameObject::getBounce�oefficient() const
	{
		return bounce_coefficient;
	}

	// �������� ������������ ������� ����������� (Minimum Translation Vector, MTV)
	CollisionSide GameObject::getCollisionVector(GameObject& object) const
	{
		Vect position2 = object.position;
		Vect half_size2 = object.half_size;

		// �������� �����������
		if (position2.x + half_size2.x < position.x - half_size.x
			|| position.x + half_size.x < position2.x - half_size2.x
			|| position2.y + half_size2.y < position.y - half_size.y
			|| position.y + half_size.y < position2.y - half_size2.y) {
			return NONE;
		}

		// ���������� ������������ ������� �����������
		float overlapX = std::min(position.x + half_size.x, position2.x + half_size2.x) -
			std::max(position.x - half_size.x, position2.x - half_size2.x);
		float overlapY = std::min(position.y + half_size.y, position2.y + half_size2.y) -
			std::max(position.y - half_size.y, position2.y - half_size2.y);

		if (overlapX > overlapY) {
			return (position.y < position2.y) ? TOP_SIDE : BOTTOM_SIDE;
		}
		else {
			return (position.x < position2.x) ? LEFT_SIDE : RIGHT_SIDE;
		}
	}

	void GameObject::handleCollision(GameObject& object, CollisionSide side)
	{
	}

	void GameObject::update(float elapsed)
	{
		position += velocity * elapsed;
	}

	void GameObject::draw(ImDrawList& draw_list)
	{
	}
}
