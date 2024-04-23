#pragma once

#include "base.h"
#include "arkanoid_debug.h"

class GameWorld
{
private:
	ImGuiIO& io;
	Vect size;
	Vect coords_to_screen;
	bool oldKeysDown[512];

	uint32_t score = 0;
	uint32_t lifes = 3;
	ArkanoidSettings& settings;
	ArkanoidDebug *debug;
public:
	bool paused = false;
	bool step = false;
	const uint32_t MAX_LIFES = 5;

	bool keyPressed(uint32_t key, bool once = false);

	GameWorld(ArkanoidSettings& settings, ImGuiIO& io, Vect size);
	~GameWorld();
	Vect getSize();
	ArkanoidDebug& getDebug();

	void addScore(uint32_t plus);
	void subLife();
	uint32_t getLifes() const;

	void update(float elapsed);
	bool draw(ImDrawList& draw_list);
	void updateKeys();
	float toScreenCoords(float position);
	Vect toScreenCoords(Vect position);
};
