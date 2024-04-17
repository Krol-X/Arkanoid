#pragma once

#include "base.h"
#include "imgui_impl_glfw.h"
#include "game_world.h"

class GameObject
{
protected:
	GameWorld* world;
	Vect position;
public:
	GameObject(GameWorld* world);

	virtual void update(ImGuiIO* io, float elapsed) = 0;
	virtual void draw(ImGuiIO* io, ImDrawList* draw_list) = 0;
};
