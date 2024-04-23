#include "arkanoid_debug.h"

ArkanoidDebug::ArkanoidDebug(GameWorld& world, ArkanoidSettings& settings)
	: world(world), settings(settings)
{
}

void ArkanoidDebug::addHit(const Vect& position, const Vect& normal)
{
	Hit hit;
	hit.screen_pos = world.toScreenCoords(position);
	hit.normal = normal;
	hits.push_back(std::move(hit));
}

void ArkanoidDebug::update(ImGuiIO& io, float elapsed)
{
	size_t remove_by_timeout_count = 0;
	for (auto& hit : hits)
	{
		hit.time += elapsed;
		if (hit.time > settings.debug_draw_timeout)
			remove_by_timeout_count++;
	}

	// cleat outdated debug info
	if (remove_by_timeout_count > 0)
	{
		std::rotate(hits.begin(),
			hits.begin() + remove_by_timeout_count,
			hits.end());

		hits.resize(hits.size() - remove_by_timeout_count);
	}

}

void ArkanoidDebug::draw(ImGuiIO& io, ImDrawList& draw_list)
{
	const float len = settings.debug_draw_normal_length;
	for (const auto& hit : hits)
	{
		draw_list.AddCircleFilled(hit.screen_pos, settings.debug_draw_pos_radius, ImColor(255, 255, 0));
		draw_list.AddLine(hit.screen_pos, hit.screen_pos + hit.normal * len, ImColor(255, 0, 0));
	}
}


