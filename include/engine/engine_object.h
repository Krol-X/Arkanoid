#pragma once

#include "event_dispatcher.h"

class EngineObject
{
public:
	EngineObject(Vect position, Vect size);
	virtual void handleEvent(const EventType event, EventParams params) = 0;
protected:
	// Position of object center
	Vect position;
	// Object size
	Vect size;
	// Half size (for optimize)
	Vect half_size;
};

typedef std::vector<EngineObject&> EngineObjectArray;
