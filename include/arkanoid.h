#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "imgui_impl_glfw.h"
#include <irrKlang.h>

#include "arkanoid_settings.h"
#include "game/ball.h"
#include "game/carriage.h"
#include <game/brick.h>


class Arkanoid {
public:
	Arkanoid(ArkanoidSettings& settings);
	bool isInited() const;
	void reset(ArkanoidSettings& settings);
	void Run();
	~Arkanoid();

private:
	const char* glsl_version;
	GLFWwindow* window = NULL;
	ImGuiIO* io = NULL;
	irrklang::ISoundEngine* soundEngine = NULL;

	irrklang::ISound* music;
	irrklang::ISoundSource* wall_sound;
	irrklang::ISoundSource* brick_sound;
	irrklang::ISoundSource* die_sound;

	bool inited = false;
	bool need_reset = false;
	float render_elapsed_time = 0.0f;

	ArkanoidSettings& settings;
	GameWorld* world = NULL;
	Ball* ball = NULL;
	Carriage* carriage = NULL;
	std::vector<Brick*> bricks;

	bool initGlfw();
	void initImGui();
	void initAudio();
	void initGame();
	void update();
	void doneGame();
	void generateBricks();
	void checkCollisions();
	void render(ImDrawList& drawList);
};
