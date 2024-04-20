#pragma once

#include "engine_object.h"

class EngineContainer : EngineObject
{
public:
	EngineContainer(Vect position, Vect size);
	void handleEvent(const EventType event, EventParams params);
protected:
	EngineObjectArray content;
	EventDispatcher& dispatcher;
};
