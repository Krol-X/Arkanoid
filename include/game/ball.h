#pragma once

#include "engine/game_object.h"

class Ball : public GameObject
{
public:
	Ball(Vect position, float radius, Vect velocity);
	void handleEvent(const EventType event, EventParams& params);
private:
	void update(EventParams& params);
	void draw(EventParams& params);
};
