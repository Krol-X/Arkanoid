#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "imgui_impl_glfw.h"
#include "game_settings.h"
#include "game/ball.h"
#include "game/carriage.h"
#include <game/brick.h>

class Game {
public:
    Game();
    bool isInited() const;
    void Run();
    ~Game();

private:
    const char* glsl_version;
    GLFWwindow* window = nullptr;
    ImGuiIO* io = nullptr;
    GameSettings settings;

    bool inited = false;
    bool paused = true;
    float render_elapsed_time = 0.0f;

    GameWorld* world;
    Ball* ball;
    Carriage* carriage;
    std::vector<Brick*> bricks;

    bool initGlfw();
    void initImGui();
    void initGame();
    void generateBricks();
    void update();
    void checkCollisions();
    void render(ImDrawList& drawList);
};
