#include "engine/event_dispatcher.h"

EventDispatcher::EventDispatcher(EngineObjectArray& content,
	DispatchMode update_mode, DispatchMode draw_mode)
	: content(content)
{
	if (update_mode == ONCE_FIRST) {
		update_queue = { &update_once, &update_always };
	}
	else {
		update_queue = { &update_always, &update_once };
	}

	if (draw_mode == ONCE_FIRST) {
		draw_queue = { &draw_once, &draw_always };
	}
	else {
		draw_queue = { &draw_always, &draw_once };
	}
}

void EventDispatcher::doEvent(EventType event, EventParams params)
{
	switch (event)
	{
	case EVENT_UPDATE:
		for (auto& queue : update_queue)
		{
			for (auto& obj : queue)
				obj.handleEvent(event, params);
		}
		update_once.clear();
		break;
	case EVENT_DRAW:
		for (auto& queue : draw_queue)
		{
			for (auto& obj : queue)
				obj.handleEvent(event, params);
		}
		draw_once.clear();
		break;
	case EVENT_DESTROY:
		for (auto& obj : to_destory) {
			obj.handleEvent(event, params);
			content.erase(std::remove(content.begin(), content.end(), obj), content.end());
		}
		to_destory.clear();
		break;
	}
}

void EventDispatcher::addToUpdate(EngineObject& object, EventMode mode)
{
	if (mode == ONCE_REPEAT)
		update_once.push_back(object);
	else
		update_always.push_back(object);
}

void EventDispatcher::addToDraw(EngineObject& object, EventMode mode)
{
	if (mode == ONCE_REPEAT)
		draw_once.push_back(object);
	else
		draw_always.push_back(object);
}

void EventDispatcher::addToDestroy(EngineObject& object)
{
	to_destory.push_back(object);
}