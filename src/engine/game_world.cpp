#include "engine/game_world.h"
#include <string>

bool GameWorld::keyPressed(uint32_t key, bool once)
{
	bool key_down = io.KeysDown[key];
	if (once)
		key_down &= key_down != oldKeysDown[key];
	return key_down;
}

GameWorld::GameWorld(ArkanoidSettings& settings, ImGuiIO& io, Vect size) : io(io), settings(settings)
{
	this->size = size;
	lifes = MAX_LIFES;
	memset(oldKeysDown, 0, sizeof(oldKeysDown[0]));
	debug = new ArkanoidDebug(*this, settings);
}

GameWorld::~GameWorld()
{
	delete debug;
}

ArkanoidDebug& GameWorld::getDebug()
{
	return *debug;
}

Vect GameWorld::getSize()
{
	return size;
}

void GameWorld::addScore(uint32_t plus)
{
	score += plus;
}

void GameWorld::subLife()
{
	lifes--;
}

uint32_t GameWorld::getLifes() const
{
	return lifes;
}

void GameWorld::update(float elapsed)
{
	coords_to_screen = Vect(io.DisplaySize.x / size.x, io.DisplaySize.y / size.y);
	debug->update(io, elapsed);
}

void GameWorld::updateKeys()
{
	memcpy(oldKeysDown, io.KeysDown, sizeof(oldKeysDown));
}

bool GameWorld::draw(ImDrawList& draw_list)
{
	ImVec2 textPos(0, 0);
	ImU32 textColor = ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

	char textBuffer[50];
	sprintf(textBuffer, "Score: %u\nLifes: %u", score, lifes);
	std::string textString(textBuffer);

	draw_list.AddText(ImGui::GetIO().Fonts->Fonts[0], 32.0f, textPos, textColor, textString.c_str());

	if (settings.debug_draw)
	{
		debug->draw(io, draw_list);
	}
	if (settings.gui_draw)
	{
		debug->drawDebugWindow(io, draw_list);
		if (debug->drawSettingsWindow(io, draw_list))
			return true;
	}
	return false;
}

float GameWorld::toScreenCoords(float position)
{
	return position * coords_to_screen.x;
}

Vect GameWorld::toScreenCoords(Vect position)
{
	return position * coords_to_screen;
}
