#pragma once

#include "../base/game_object.h"

class Ball : public GameObject
{
private:
	Vect velocity;
	float radius;
public:
	Ball(GameWorld *world, Vect position, float radius, Vect velocity);
	
	void update(ImGuiIO* io, float elapsed);
	void draw(ImGuiIO* io, ImDrawList* draw_list);
};
