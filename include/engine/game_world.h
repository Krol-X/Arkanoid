#pragma once

#include "base.h"

class GameWorld
{
private:
	ImGuiIO& io;
	Vect size;
	Vect coords_to_screen;
	bool oldKeysDown[512];

	uint32_t score = 0;
	uint32_t lifes = 3;
public:
	const uint32_t MAX_LIFES = 5;

	bool keyPressed(uint32_t key, bool once = false);

	GameWorld(ImGuiIO& io, Vect size);
	Vect getSize();

	void addScore(uint32_t plus);
	void subLife();
	uint32_t getLifes() const;

	void update(float elapsed);
	void draw(ImDrawList& draw_list);
	void updateKeys();
	float toScreenCoords(float position);
	Vect toScreenCoords(Vect position);
};
