#pragma once

#include "base.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "arkanoid.h"

struct ArkanoidSettingsExtended : ArkanoidSettings
{
	bool step_by_step = false;
	bool debug_draw = false;
	float debug_draw_pos_radius = 5.0f;
	float debug_draw_normal_length = 30.0f;
	float debug_draw_timeout = 0.5f;
};

class Game {
private:
	const char* glsl_version;
	GLFWwindow* window;
	ImGuiIO* io;
	ArkanoidDebugData arkanoid_debug_data;
	ArkanoidSettingsExtended arkanoid_settings;
	Arkanoid* arkanoid;
	bool do_arkanoid_update;
	bool init_ok;

	bool initGlfw();
	void initImGui();
	bool isInitOk();
	void renderSettingsWindow();
	void renderDebugWindow();
	void renderGame(ImDrawList* bg_drawlist, float elapsed_time);
	void renderDebug(ImDrawList* bg_drawlist);
public:

	Game();
	void Run();
	~Game();
};
