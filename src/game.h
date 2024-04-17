#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "imgui_impl_glfw.h"
#include "game_settings.h"
#include "objects/ball.h"

class Game {
public:
	Game();
	bool isInited();
	void Run();
	~Game();

private:
	const char* glsl_version;
	GLFWwindow* window;
	ImGuiIO* io;
	GameSettings settings;

	bool inited;
	bool paused;
	float render_elapsed_time;

	GameWorld* world;
	Ball* ball;

	bool initGlfw();
	void initImGui();
	void initGame();
	void update();
	void render(ImDrawList* draw_list);
};
