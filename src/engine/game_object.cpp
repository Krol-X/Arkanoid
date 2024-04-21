#include "engine/game_object.h"

GameObject::GameObject(Vect position, Vect size, Vect velocity = Vect(0.f))
	: EngineObject(position, size), velocity(velocity)
{
}

void GameObject::handleEvent(const EventType event, EventParams& params)
{
	switch (event)
	{
		case EVENT_UPDATE:
			position = position + velocity * params.elapsed;
			break;
		default:
			break;
	}
}

const Vect& GameObject::getVelocity() const
{
	return velocity;
}
