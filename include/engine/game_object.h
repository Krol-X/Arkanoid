#pragma once

#include "engine_object.h"

class GameObject : EngineObject
{
public:
	GameObject(Vect position, Vect size, Vect velocity);
	void handleEvent(const EventType event, EventParams params);
protected:
	Vect velocity;
};
