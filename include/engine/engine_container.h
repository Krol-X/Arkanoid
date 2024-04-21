#pragma once

#include "engine/event_dispatcher.h"
#include "engine/engine_object.h"

class EngineContainer : public EngineObject
{
public:
	EngineContainer(Vect position, Vect size);
	~EngineContainer();
	void handleEvent(const EventType event, EventParams& params);
protected:
	EngineObjectArray content;
	EventDispatcher* dispatcher;
};
