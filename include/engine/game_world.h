#pragma once

#include "base.h"

class GameWorld
{
private:
	Vect size;
	Vect coords_to_screen;

	uint32_t score = 0;
	uint32_t lifes = 3;
public:
	GameWorld(Vect size);
	Vect getSize();

	void addScore(uint32_t plus);
	void subLife();
	uint32_t getLifes() const;

	void update(ImGuiIO& io, float elapsed);
	void draw(ImGuiIO& io, ImDrawList& draw_list);
	float toScreenCoords(float position);
	Vect toScreenCoords(Vect position);
};
