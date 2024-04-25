#include "engine/systems/audio.h"

namespace Engine::Systems
{
	Audio::Audio()
	{
		engine = irrklang::createIrrKlangDevice();
	}

	Audio::~Audio()
	{
		engine->drop();
	}

	irrklang::ISoundEngine* Audio::getEngine()
	{
		return engine;
	}

	int Audio::load(char* filename)
	{
		if (!engine)
			return -1;
		auto audio = engine->addSoundSourceFromFile(filename, irrklang::ESM_AUTO_DETECT, true);
		data.push_back(audio);
		return data.size() - 1;
	}

	void Audio::play(int id)
	{
		if (!engine)
			return;

		if (id >= 0 || id < data.size())
		{
			auto audio = data[id];
			if (audio) {
				irrklang::ISound* sound = engine->play2D(audio);
			}
		}
	}
}
