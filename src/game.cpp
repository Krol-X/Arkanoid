#include "game.h"

#include <stdio.h>

#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"



static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}



Game::Game()
{
	this->init_ok = false;

	if (!this->initGlfw())
		return;
	this->initImGui();

	this->arkanoid = create_arkanoid();
	this->arkanoid->reset(this->arkanoid_settings);

	this->init_ok = true;
}



bool Game::isInitOk()
{
	return this->init_ok;
}



Game::~Game()
{
	// fixit
	if (this->isInitOk()) {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(this->window);
		glfwTerminate();
	}
}



void Game::Run()
{
	ImVec4 clear_color = ImVec4(0.05f, 0.075f, 0.1f, 1.00f);

	// Main loop
	double last_time = glfwGetTime();
	while (!glfwWindowShouldClose(this->window))
	{
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();

		double cur_time = glfwGetTime();
		float elapsed_time = static_cast<float>(std::min(cur_time - last_time, 1.0));
		last_time = cur_time;

		this->do_arkanoid_update = true;

		renderSettingsWindow();
		renderDebugWindow();

		ImDrawList* bg_drawlist = ImGui::GetBackgroundDrawList();
		renderGame(bg_drawlist, elapsed_time);
		if (arkanoid_settings.debug_draw) {
			renderDebug(bg_drawlist);
		}

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(this->window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(this->window);
	}
}



bool Game::initGlfw()
{
	// Setup window
	glfwSetErrorCallback(glfw_error_callback);

	if (!glfwInit()) {
		fprintf(stderr, "Failed to init GLFW!\n");
		return false;
	}

	// Decide GL+GLSL versions
#ifdef __APPLE__
	// GL 3.2 + GLSL 150
	this->glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	this->glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

	// Create window with graphics context
	this->window = glfwCreateWindow(960, 540, "My Arkanoid", NULL, NULL);
	if (this->window == NULL) {
		fprintf(stderr, "Failed to create window!\n");
		return false;
	}

	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1); // Enable vsync

	if (!gladLoadGL(glfwGetProcAddress))
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return false;
	}
	return true;
}



void Game::initImGui()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	this->io = &ImGui::GetIO();

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer back-ends
	ImGui_ImplGlfw_InitForOpenGL(this->window, true);
	ImGui_ImplOpenGL3_Init(this->glsl_version);
}



void Game::renderSettingsWindow()
{
	ImGui::Begin("Arkanoid");

	ImGui::InputFloat2("World size", this->arkanoid_settings.world_size.data_);

	ImGui::Spacing();
	ImGui::SliderInt("Bricks columns", &this->arkanoid_settings.bricks_columns_count, ArkanoidSettings::bricks_columns_min, ArkanoidSettings::bricks_columns_max);
	ImGui::SliderInt("Bricks rows", &this->arkanoid_settings.bricks_rows_count, ArkanoidSettings::bricks_rows_min, ArkanoidSettings::bricks_rows_max);

	ImGui::SliderFloat("Bricks padding columns", &this->arkanoid_settings.bricks_columns_padding, ArkanoidSettings::bricks_columns_padding_min, ArkanoidSettings::bricks_columns_padding_max);
	ImGui::SliderFloat("Bricks padding rows", &this->arkanoid_settings.bricks_rows_padding, ArkanoidSettings::bricks_rows_padding_min, ArkanoidSettings::bricks_rows_padding_max);

	ImGui::Spacing();
	ImGui::SliderFloat("Ball radius", &this->arkanoid_settings.ball_radius, ArkanoidSettings::ball_radius_min, ArkanoidSettings::ball_radius_max);
	ImGui::SliderFloat("Ball speed", &this->arkanoid_settings.ball_speed, ArkanoidSettings::ball_speed_min, ArkanoidSettings::ball_speed_max);

	ImGui::Spacing();
	ImGui::SliderFloat("Carriage width", &this->arkanoid_settings.carriage_width, ArkanoidSettings::carriage_width_min, this->arkanoid_settings.world_size.x);

	if (ImGui::Button("Reset"))
		this->arkanoid->reset(this->arkanoid_settings);

	ImGui::End();
}



void Game::renderDebugWindow()
{
	ImGui::Begin("Arkanoid Debug");
	ImGui::Checkbox("Debug draw", &this->arkanoid_settings.debug_draw);

	if (this->arkanoid_settings.debug_draw)
	{
		ImGui::SliderFloat("Hit pos radius", &this->arkanoid_settings.debug_draw_pos_radius, 3.0f, 15.0f);
		ImGui::SliderFloat("Hit normal length", &this->arkanoid_settings.debug_draw_normal_length, 10.0f, 100.0f);
		ImGui::SliderFloat("Timeout", &this->arkanoid_settings.debug_draw_timeout, 0.1f, 10.0f);
	}

	ImGui::Spacing();
	ImGui::Checkbox("Steps by step", &this->arkanoid_settings.step_by_step);

	if (this->arkanoid_settings.step_by_step)
		this->do_arkanoid_update = false;

	if (ImGui::Button("Next step (SPACE Key)") || this->io->KeysDown[GLFW_KEY_SPACE])
		this->do_arkanoid_update = true;

	ImGui::End();
}



void Game::renderGame(ImDrawList* bg_drawlist, float elapsed_time)
{
	if (this->do_arkanoid_update)
	{
		this->arkanoid->update(*this->io, arkanoid_debug_data, elapsed_time);

		// update debug draw data time
		size_t remove_by_timeout_count = 0;
		for (auto& hit : arkanoid_debug_data.hits)
		{
			hit.time += elapsed_time;
			if (hit.time > arkanoid_settings.debug_draw_timeout)
				remove_by_timeout_count++;
		}

		// cleat outdated debug info
		if (remove_by_timeout_count > 0)
		{
			std::rotate(arkanoid_debug_data.hits.begin(),
				arkanoid_debug_data.hits.begin() + remove_by_timeout_count,
				arkanoid_debug_data.hits.end());

			arkanoid_debug_data.hits.resize(arkanoid_debug_data.hits.size() - remove_by_timeout_count);
		}
	}

	this->arkanoid->draw(*this->io, *bg_drawlist);
}



void Game::renderDebug(ImDrawList* bg_drawlist)
{
	const float len = arkanoid_settings.debug_draw_normal_length;
	for (const auto& hit : arkanoid_debug_data.hits)
	{
		bg_drawlist->AddCircleFilled(hit.screen_pos, arkanoid_settings.debug_draw_pos_radius, ImColor(255, 255, 0));
		bg_drawlist->AddLine(hit.screen_pos, hit.screen_pos + hit.normal * len, ImColor(255, 0, 0));
	}
}
