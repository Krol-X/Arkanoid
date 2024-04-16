#pragma once

#include "../base/game_object.h"

class Ball : GameObject
{
private:
	Vect velocity;
	float radius;
public:
	void draw(ImGuiIO& io, ImDrawList& draw_list);
	void update(ImGuiIO& io, float elapsed);
};
