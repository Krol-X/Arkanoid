#pragma once

#include "base.h"

class GameWorld
{
private:
	Vect size;
	Vect coords_to_screen;

public:
	GameWorld(Vect size);
	Vect getSize();

	void update(ImGuiIO& io, float elapsed);
	float toScreenCoords(float position);
	Vect toScreenCoords(Vect position);
};
