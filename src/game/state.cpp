#include "game/state.h"

namespace Game
{
	State::State(
		ArkanoidSettings& game_settings,
		LevelSettings& level_settings,
		Io& io,
		Audio& audio,
		Debug& debug,
		GamePlay& gameplay
	)
		: game_settings(game_settings)
		, level_settings(level_settings)
		, io_system(io)
		, audio_system(audio)
		, debug_system(debug)
		, gameplay_system(gameplay)
	{}

	void State::LoadSettings(ArkanoidSettings& game_settings, LevelSettings& level_settings)
	{
		this->game_settings = game_settings;
		this->level_settings = level_settings;
	}

	ArkanoidSettings& State::arkanoidSettings() const
	{
		return game_settings;
	}

	LevelSettings& State::levelSettings() const
	{
		return level_settings;
	}

	Io& State::io() const
	{
		return io_system;
	}

	Audio& State::audio() const
	{
		return audio_system;
	}

	Debug& State::debug() const
	{
		return debug_system;
	}

	GamePlay& State::gameplay() const
	{
		return gameplay_system;
	}
}
