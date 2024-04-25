#include "arkanoid.h"
#include <ctime>

Arkanoid::Arkanoid(ArkanoidSettings& game_settings, LevelSettings& level_settings)
{
	std::srand(std::time(0));
	io_system = new Io();
	audio_system = new Audio();
	debug_system = new Debug();
	gameplay_system = new GamePlay();

	state = new State(
		game_settings,
		level_settings,
		*io_system,
		*audio_system,
		*debug_system,
		*gameplay_system
	);
	io_system->init(state);
	debug_system->init(state);
	gameplay_system->init(state);

	auto engine = audio_system->getEngine();
	engine->setSoundVolume(0.5f);
	auto music = engine->play2D("back_music.mp3", true, false, true);
	if (music) {
		music->setVolume(0.5f);
	}
}

void Arkanoid::reset(LevelSettings& level_settings)
{
	state->LoadSettings(game_settings, level_settings);
}

void Arkanoid::run()
{
	auto gameplay = state->gameplay();

	gameplay.setAlive();
	while (gameplay.isAlive())
	{
		gameplay.step();
		if (!gameplay.isAlive() && gameplay.isNeedReset())
		{
			delete gameplay_system;
			gameplay_system = new GamePlay();
			gameplay_system->init(state);
			gameplay.setAlive();
		}
	}
}

Arkanoid::~Arkanoid()
{
	delete state;
	delete gameplay_system;
	delete debug_system;
	delete audio_system;
	delete io_system;
}
