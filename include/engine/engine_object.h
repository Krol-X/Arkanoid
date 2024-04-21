#pragma once

#include "base.h"

enum EventType;
struct EventParams;

class EngineObject
{
public:
	EngineObject(Vect position, Vect size);
	virtual void handleEvent(const EventType event, EventParams& params) = 0;
	
	const Vect& getPosition() const;
	const Vect& getSize() const;
	const Vect& getHalfSize() const;
protected:
	// Position of object center
	Vect position;
	// Object size
	Vect size;
	// Half size (for optimize)
	Vect half_size;
};

typedef std::vector<EngineObject&> EngineObjectArray;

#include "engine/event_dispatcher.h"
