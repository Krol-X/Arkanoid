#include "engine/engine_object.h"

EngineObject::EngineObject(Vect position, Vect size)
	: position(position), size(size)
{
}

const Vect& EngineObject::getPosition() const { return position; }
const Vect& EngineObject::getSize() const { return size; }
const Vect& EngineObject::getHalfSize() const { return half_size; }
