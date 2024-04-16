#pragma once

#include "base.h"
#include "imgui_impl_glfw.h"
#include "game_world.h"

class GameObject
{
protected:
	GameWorld& world;
public:
	Vect position;

	GameObject(GameWorld& world);
	virtual void draw(ImGuiIO& io, ImDrawList& draw_list) = 0;
	virtual void update(ImGuiIO& io, float elapsed) = 0;
};
