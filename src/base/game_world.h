#pragma once

#include "base.h"

class GameWorld
{
private:
	Vect coords_to_screen;

public:
	Vect size;

	void update(ImGuiIO& io, float elapsed);
	float toScreenCoords(float position);
	Vect toScreenCoords(Vect position);
};
