#pragma once

#include "base.h"
#include "arkanoid_settings.h"

class GameWorld;

struct ArkanoidDebug
{
public:
    ArkanoidDebug(GameWorld& world, ArkanoidSettings& settings);
    ~ArkanoidDebug() = default;

    void addHit(const Vect& pos, const Vect& normal);
    void update(ImGuiIO& io, float elapsed);
    bool draw(ImGuiIO& io, ImDrawList& draw_list);
    bool drawSettingsWindow(ImGuiIO& io, ImDrawList& draw_list);
    void drawDebugWindow(ImGuiIO& io, ImDrawList& draw_list);
private:
    struct Hit
    {
        Vect screen_pos;        // Hit position, in screen space
        Vect normal;            // Hit normal
        float time = 0.0f;      // leave it default
    };

    ArkanoidSettings& settings;
    GameWorld& world;
    std::vector<Hit> hits;
};

#include "engine/game_world.h"
