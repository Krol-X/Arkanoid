#pragma once

#include "game/state.h"

using Settings::ArkanoidSettings;
using Settings::LevelSettings;
using Engine::Systems::Io;
using Engine::Systems::Audio;
using Engine::Systems::Debug;
using Game::State;
using Game::GamePlay;

class Arkanoid {
public:
	Arkanoid(ArkanoidSettings& game_settings, LevelSettings& level_settings);
	~Arkanoid();
	void reset(LevelSettings& level_settings);
	void run();
private:
	ArkanoidSettings game_settings;
	LevelSettings level_settings;
	Io *io_system;
	Audio *audio_system;
	Debug *debug_system;
	GamePlay *gameplay_system;

	State* state;
	int audio_music_id;
};
