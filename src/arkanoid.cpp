#include "arkanoid.h"

#include <cstdio>
#include <ctime>
#define _USE_MATH_DEFINES
#include <cmath>

#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}



Arkanoid::Arkanoid(ArkanoidSettings& settings)
	:settings(settings)
{
	inited = false;

	if (!initGlfw())
		return;
	initImGui();
	initAudio();
	initGame();

	inited = true;
}

Arkanoid::~Arkanoid()
{
	if (inited) {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(window);
		glfwTerminate();

		soundEngine->drop();
		doneGame();
	}
}

bool Arkanoid::isInited() const
{
	return inited;
}

void Arkanoid::reset(ArkanoidSettings& settings)
{
	this->settings = settings;
	doneGame();
	initGame();
}

void Arkanoid::Run()
{
	if (!inited)
		return;

	ImVec4 clear_color = ImVec4(0.05f, 0.075f, 0.1f, 1.00f);

	double last_time = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();

		double cur_time = glfwGetTime();
		render_elapsed_time = static_cast<float>(std::min(cur_time - last_time, 1.0));
		last_time = cur_time;

		update();
		if (!world->getLifes())
		{	
			reset(settings);
		}
			
		ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
		render(*draw_list);

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}
}

bool Arkanoid::initGlfw()
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
	glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

	// Create window with graphics context
	window = glfwCreateWindow(800, 600, "Arkanoid", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to create window!\n");
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	if (!gladLoadGL(glfwGetProcAddress))
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return false;
	}
	return true;
}

void Arkanoid::initImGui()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO();

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer back-ends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void Arkanoid::initAudio()
{
	soundEngine = irrklang::createIrrKlangDevice();
	soundEngine->setSoundVolume(0.5f);
	music = soundEngine->play2D("back_music.mp3", true, false, true);
	if (music) {
		music->setVolume(0.5f);
	}
	wall_sound = soundEngine->addSoundSourceFromFile("wall.wav", irrklang::ESM_AUTO_DETECT, true);
	brick_sound = soundEngine->addSoundSourceFromFile("brick.wav", irrklang::ESM_AUTO_DETECT, true);
	die_sound = soundEngine->addSoundSourceFromFile("die.wav", irrklang::ESM_AUTO_DETECT, true);
}

void Arkanoid::initGame()
{
	std::srand(std::time(0));
	
	world = new GameWorld(*io, settings.world_size);
	Vect world_size = world->getSize();

	Vect ball_pos = Vect(world_size.x / 2.0f, world_size.y / 2.0f);

	float random_angle = (std::rand() % 61 + 45) * M_PI / 180.0f;

	// ¬ычисл€ем компоненты вектора скорости на основе заданной скорости и случайного угла
	float x_vel = settings.ball_speed * std::cos(random_angle);
	float y_vel = settings.ball_speed * std::sin(random_angle);
	Vect ball_vel = Vect(x_vel, y_vel);

	ball = new Ball(*world, ball_pos, settings.ball_radius, ball_vel);

	Vect& carriage_size = settings.carriage_size;
	Vect carriage_pos = Vect(world_size.x / 2.0f, world_size.y - carriage_size.y - 10.0f);
	carriage = new Carriage(*world, carriage_pos, carriage_size);

	generateBricks();

	world->updateKeys();
	paused = false;
}

void Arkanoid::doneGame()
{
	if (world)
		delete world;
	world = NULL;
	if (ball)
		delete ball;
	ball = NULL;
	if (carriage)
		delete carriage;
	carriage = NULL;

	for (auto& brick : bricks)
	{
		delete brick;
		brick = nullptr;
	}
	bricks.clear();
}


void Arkanoid::generateBricks()
{
	float bricks_width = (settings.world_size.x - (settings.bricks_columns_count + 1.0f) * settings.bricks_columns_padding) / settings.bricks_columns_count;
	float bricks_height = (settings.world_size.y / 3.0f - (settings.bricks_rows_count + 1.0f) * settings.bricks_rows_padding) / settings.bricks_rows_count;

	float start_x = settings.bricks_columns_padding + bricks_width / 2.0f;
	float start_y = bricks_height;

	for (int row = 0; row < settings.bricks_rows_count; ++row)
	{
		for (int col = 0; col < settings.bricks_columns_count; ++col)
		{
			float brick_x = start_x + col * (bricks_width + settings.bricks_columns_padding);
			float brick_y = start_y + row * (bricks_height + settings.bricks_rows_padding);
			Vect brick_pos(brick_x, brick_y);
			Vect brick_size(bricks_width, bricks_height);
			Brick* brick = new Brick(*world, brick_pos, brick_size);
			bricks.push_back(brick);
		}
	}
}

void Arkanoid::update()
{
	bool step = false;

	world->update(render_elapsed_time);

	if (world->keyPressed(GLFW_KEY_SPACE, true))
	{
		paused = !paused;
	}
	if (world->keyPressed(GLFW_KEY_KP_ADD, true))
	{
		step = true;
	}

	if (!paused || step) {
		auto old_lifes = world->getLifes();
		if (ball->update(*io, render_elapsed_time))
		{
			if (old_lifes != world->getLifes())
			{
				if (die_sound)
					soundEngine->play2D(die_sound);
			}
			else {
				if (wall_sound)
					soundEngine->play2D(wall_sound);
			}
		}
		carriage->update(*io, render_elapsed_time);
		checkCollisions();
	}

	world->updateKeys();
}

void Arkanoid::checkCollisions()
{
	std::vector<Brick*> bricksToRemove;

	auto collsion = ball->getCollisionVector(*carriage);
	if (collsion)
	{
		ball->handleCollision(*carriage, collsion);
		if (wall_sound)
			soundEngine->play2D(wall_sound);
	}

	for (Brick* brick : bricks)
	{
		auto collsion = ball->getCollisionVector(*brick);
		if (collsion)
		{
			ball->handleCollision(*brick, collsion);
			if (brick->handleCollision(*ball, collsion))
			{
				bricksToRemove.push_back(brick);
				if (brick_sound)
					soundEngine->play2D(brick_sound);
			}
			else {
				if (wall_sound)
					soundEngine->play2D(wall_sound);
			}
			break;
		}
	}

	// Delete kicked bricks
	for (Brick* brick : bricksToRemove)
	{
		auto it = std::find(bricks.begin(), bricks.end(), brick);
		if (it != bricks.end())
		{
			bricks.erase(it);
			delete brick;
		}
	}
}

void Arkanoid::render(ImDrawList& draw_list)
{
	ball->draw(*io, draw_list);
	carriage->draw(*io, draw_list);
	for (Brick* brick : bricks)
	{
		brick->draw(*io, draw_list);
	}
	world->draw(draw_list);
}
