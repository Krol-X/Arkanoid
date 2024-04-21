#include "engine/engine_container.h"

EngineContainer::EngineContainer(Vect position, Vect size)
	: EngineObject(position, size)
{
	dispatcher = new EventDispatcher(content, ONCE_FIRST, ONCE_FIRST);
}

EngineContainer::~EngineContainer()
{
	delete dispatcher;
}

void EngineContainer::handleEvent(const EventType event, EventParams& params)
{
	params.parent = this;
	dispatcher->doEvent(event, params);
}
