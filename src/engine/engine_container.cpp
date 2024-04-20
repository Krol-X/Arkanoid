#include "engine/engine_container.h"

EngineContainer::EngineContainer(Vect position, Vect size)
	: EngineObject(position, size),
	dispatcher(EventDispatcher(content, ONCE_FIRST, ONCE_FIRST))
{
}

void EngineContainer::handleEvent(const EventType event, EventParams params)
{
	params.parent = this;
	dispatcher.doEvent(event, params);
}
