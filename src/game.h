#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "imgui_impl_glfw.h"

class Game {
public:
	Game();
	void Run();
	~Game();

private:
	const char* glsl_version;
	GLFWwindow* window;
	ImGuiIO* io;
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
};
