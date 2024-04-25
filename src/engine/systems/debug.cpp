#include "engine/systems/debug.h"

// hits утечка памяти?
namespace Engine::Systems
{
	Debug::Debug()
		: state(NULL), elapsed_total(0.f), frame_count(0), fps(0)
	{
	}

	void Debug::init(State* state)
	{
		this->state = state;
	}

	Debug::~Debug()
	{
		hits.empty();
	}

	void Debug::addHit(const Vect& position, const Vect& normal)
	{
		Hit hit;
		hit.screen_pos = state->io().translateCoords(position);
		hit.normal = normal;
		hits.push_back(std::move(hit));
	}

	void Debug::update(float elapsed)
	{
		// check outdated debug info
		size_t remove_by_timeout_count = 0;
		for (auto& hit : hits)
		{
			hit.time += elapsed;
			if (hit.time > state->levelSettings().debug_draw_timeout)
				remove_by_timeout_count++;
		}

		// clear outdated debug info
		if (remove_by_timeout_count > 0)
		{
			std::rotate(hits.begin(),
				hits.begin() + remove_by_timeout_count,
				hits.end());

			hits.resize(hits.size() - remove_by_timeout_count);
		}

		// calculate FPS
		frame_count++;
		elapsed_total += elapsed;
		if (elapsed_total > 1.0f)
		{
			fps = frame_count;
			frame_count = 0;
			elapsed_total -= 1.0f;
		}
	}

	const std::vector<Debug::Hit>& Debug::getHits() const
	{
		return hits;
	}

	int Debug::getFps() const
	{
		return fps;
	}
}