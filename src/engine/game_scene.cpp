#include "engine/game_scene.h"

GameScene::GameScene(Vect size, const ImGuiIO& io)
	: EngineContainer(Vect(0.f), size)
{
	
}

void GameScene::handleEvent(const EventType event, EventParams& params)
{
	switch (event)
	{
	EVENT_UPDATE:
		update(params.io);
	default:
		break;
	}
}

void GameScene::update(const ImGuiIO& io)
{
	coords_to_screen = Vect(io.DisplaySize.x / size.x, io.DisplaySize.y / size.y);
}

Vect GameScene::toScreenCoords(Vect point)
{
	return Vect();
}
