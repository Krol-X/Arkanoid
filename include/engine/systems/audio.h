#pragma once

#include "base.h"
#include <irrKlang.h>

namespace Engine::Systems
{
	class Audio {
	public:
		Audio();
		~Audio();
		irrklang::ISoundEngine* getEngine();
		int load(char* filename);
		void play(int id);
	private:
		irrklang::ISoundEngine* engine;
		std::vector<irrklang::ISoundSource*> data;
	};
}
