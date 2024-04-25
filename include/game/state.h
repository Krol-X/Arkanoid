#pragma once

#include "settings/arkanoid_settings.h"
#include "settings/level_settings.h"
#include "engine/systems/io.h"
#include "engine/systems/audio.h"
#include "engine/systems/debug.h"
#include "game/gameplay.h"

namespace Game
{
	using Settings::ArkanoidSettings;
	using Settings::LevelSettings;
	using Engine::Systems::Io;
	using Engine::Systems::Audio;
	using Engine::Systems::Debug;

	class State {
	public:
		State(
			ArkanoidSettings& game_settings,
			LevelSettings& level_settings,
			Io& io,
			Audio& audio,
			Debug& debug,
			GamePlay& gameplay
		);
		virtual ~State() = default;
		void LoadSettings(ArkanoidSettings& game_settings, LevelSettings& level_settings);

		ArkanoidSettings& arkanoidSettings() const;
		LevelSettings& levelSettings() const;
		Io& io() const;
		Audio& audio() const;
		Debug& debug() const;
		GamePlay& gameplay() const;
	private:
		ArkanoidSettings& game_settings;
		LevelSettings& level_settings;
		Io& io_system;
		Audio& audio_system;
		Debug& debug_system;
		GamePlay& gameplay_system;
	};
}
