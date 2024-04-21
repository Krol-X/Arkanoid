#pragma once

#include "engine/engine_container.h"

enum EventType
{
	EVENT_UPDATE,
	EVENT_DRAW,
	EVENT_DESTROY
};

enum EventMode
{
	ONCE_REPEAT,
	ALWAYS_REPEAT,
};

enum DispatchMode
{
	ONCE_FIRST,
	ALWAYS_FIRST
};

struct EventParams
{
	class EngineContainer* parent = NULL;
	const ImGuiIO& io;
	ImDrawList& draw_list;
	float elapsed;
};

class EventDispatcher
{
public:
	EventDispatcher(EngineObjectArray& content,
		DispatchMode update_mode, DispatchMode draw_mode);

	void doEvent(EventType event, EventParams params);

	// Add to update queue
	void addToUpdate(EngineObject& object, EventMode mode);
	// Add to draw queue
	void addToDraw(EngineObject& object, EventMode mode);
	// Add to destroy queue
	void addToDestroy(EngineObject& object);
private:
	EngineObjectArray& content;
	std::vector<EngineObjectArray&> update_queue;
	std::vector<EngineObjectArray&> draw_queue;
	EngineObjectArray update_once, update_always;
	EngineObjectArray draw_once, draw_always;
	EngineObjectArray to_destory;
};
