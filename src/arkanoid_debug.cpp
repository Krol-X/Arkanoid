#include "arkanoid_debug.h"
#include <GLFW/glfw3.h>

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

bool ArkanoidDebug::draw(ImGuiIO& io, ImDrawList& draw_list)
{
	const float len = settings.debug_draw_normal_length;
	for (const auto& hit : hits)
	{
		draw_list.AddCircleFilled(hit.screen_pos, settings.debug_draw_pos_radius, ImColor(255, 255, 0));
		draw_list.AddLine(hit.screen_pos, hit.screen_pos + hit.normal * len, ImColor(255, 0, 0));
	}
	return false;
}

bool ArkanoidDebug::drawSettingsWindow(ImGuiIO& io, ImDrawList& draw_list)
{
	bool result = false;
	ImGui::Begin("Arkanoid");

	ImGui::InputFloat2("World size", settings.world_size.data_);

	ImGui::Spacing();
	ImGui::SliderInt("Bricks columns", &settings.bricks_columns_count, ArkanoidSettings::bricks_columns_min, ArkanoidSettings::bricks_columns_max);
	ImGui::SliderInt("Bricks rows", &settings.bricks_rows_count, ArkanoidSettings::bricks_rows_min, ArkanoidSettings::bricks_rows_max);

	ImGui::SliderFloat("Bricks padding columns", &settings.bricks_columns_padding, ArkanoidSettings::bricks_columns_padding_min, ArkanoidSettings::bricks_columns_padding_max);
	ImGui::SliderFloat("Bricks padding rows", &settings.bricks_rows_padding, ArkanoidSettings::bricks_rows_padding_min, ArkanoidSettings::bricks_rows_padding_max);

	ImGui::Spacing();
	ImGui::SliderFloat("Ball radius", &settings.ball_radius, ArkanoidSettings::ball_radius_min, ArkanoidSettings::ball_radius_max);
	ImGui::SliderFloat("Ball speed", &settings.ball_speed, ArkanoidSettings::ball_speed_min, ArkanoidSettings::ball_speed_max);

	ImGui::Spacing();
	ImGui::SliderFloat("Carriage width", &settings.carriage_width, ArkanoidSettings::carriage_width_min, settings.world_size.x);

	if (ImGui::Button("Reset"))
		result = true;

	ImGui::End();
	return result;
}

void ArkanoidDebug::drawDebugWindow(ImGuiIO& io, ImDrawList& draw_list)
{
	ImGui::Begin("Arkanoid Debug");
	ImGui::Checkbox("Debug draw", &settings.debug_draw);

	if (settings.debug_draw)
	{
		ImGui::SliderFloat("Hit pos radius", &settings.debug_draw_pos_radius, 3.0f, 15.0f);
		ImGui::SliderFloat("Hit normal length", &settings.debug_draw_normal_length, 10.0f, 100.0f);
		ImGui::SliderFloat("Timeout", &settings.debug_draw_timeout, 0.1f, 10.0f);
	}

	ImGui::Spacing();
	ImGui::Checkbox("Steps by step [space]", &world.paused);
	if (world.keyPressed(GLFW_KEY_SPACE, true))
		world.paused = !world.paused;

	if (ImGui::Button("Next step [+]") || world.keyPressed(GLFW_KEY_KP_ADD, true))
		world.step = true;

	ImGui::End();
}

