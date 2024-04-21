#pragma once

#include "engine_object.h"

class GameObject : public EngineObject
{
public:
	GameObject(Vect position, Vect size, Vect velocity);
	void handleEvent(const EventType event, EventParams& params);
	
	const Vect& getVelocity() const;
protected:
	Vect velocity;
};
