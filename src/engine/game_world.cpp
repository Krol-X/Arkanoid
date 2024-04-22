#include "engine/game_world.h"
#include <string>

GameWorld::GameWorld(Vect size)
{
	this->size = size;
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
	life--;
}

void GameWorld::update(ImGuiIO& io, float elapsed)
{
	coords_to_screen = Vect(io.DisplaySize.x / size.x, io.DisplaySize.y / size.y);
}

void GameWorld::draw(ImGuiIO& io, ImDrawList& draw_list)
{
	ImVec2 textPos(0, 0);
	ImU32 textColor = ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

	char textBuffer[50];
	sprintf(textBuffer, "Score: %u\nLifes: %u", score, life);
	std::string textString(textBuffer);

	draw_list.AddText(ImGui::GetIO().Fonts->Fonts[0], 24.0f, textPos, textColor, textString.c_str());
}

float GameWorld::toScreenCoords(float position)
{
	return position * coords_to_screen.x;
}

Vect GameWorld::toScreenCoords(Vect position)
{
	return position * coords_to_screen;
}
