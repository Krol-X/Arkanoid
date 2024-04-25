#pragma once

#define IO_USE_GAME_IMPLEMENTATION

#include "base.h"
#include <imgui.h>
#include <GLFW/glfw3.h>

#ifdef IO_USE_GAME_IMPLEMENTATION
namespace Game {
	class State;
	class GamePlay;
}
#endif

namespace Engine::Systems
{
#ifdef IO_USE_GAME_IMPLEMENTATION
	using Game::State;
	typedef void(*RenderFunction)(State& state, ImDrawList& draw_list);
#else
	typedef void(*RenderFunction)(ImDrawList& draw_list);
#endif

	class Io {
	public:
		Io();
		~Io();
#ifdef IO_USE_GAME_IMPLEMENTATION
		void init(State* state);
#endif
		ImGuiIO& getIo();
		bool keyPressed(int key, bool once = false);
		void drawText(ImDrawList& draw_list, char* text, Vect position, ImVec4 color, float size);
		void setContainerSize(Vect size);
		Vect translateCoords(Vect point);
		float getElapsedTime();
		void tick(RenderFunction render);
	private:
#ifdef IO_USE_GAME_IMPLEMENTATION
		State* state;
#endif
		const char* glsl_version;
		GLFWwindow* window = nullptr;
		ImGuiIO* io;

		bool oldKeysDown[512];
		float last_time;
		float render_elapsed_time;
		Vect container_size;
		Vect coords_to_screen;
		ImVec4 clear_color;

		void initGlfw();
		void initImGui();
		void updateCoordsToScreen();
		void updateKeys();
	};
}
