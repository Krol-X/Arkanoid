#pragma once

#include "engine_container.h"

class GameScene : public EngineContainer
{
public:
	GameScene(Vect size, const ImGuiIO& io);
	void handleEvent(const EventType event, EventParams& params);
	void update(const ImGuiIO& io);
	Vect toScreenCoords(Vect point);
private:
	Vect coords_to_screen;
};
