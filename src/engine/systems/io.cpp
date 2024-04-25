#include <glad/gl.h>
#include "engine/systems/io.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <string>

namespace Engine::Systems
{
	static void glfw_error_callback(int error, const char* description)
	{
		fprintf(stderr, "Glfw Error %d: %s\n", error, description);
	}

	Io::Io()
		: render_elapsed_time(0), container_size(Vect(0.f)), coords_to_screen(1.f)
	{
		initGlfw();
		initImGui();
		clear_color = ImVec4(0.05f, 0.075f, 0.1f, 1.00f);
		last_time = glfwGetTime();
		updateKeys();
	}

	void Io::initGlfw()
	{
		// Setup window
		glfwSetErrorCallback(glfw_error_callback);

		if (!glfwInit()) {
			fprintf(stderr, "Failed to init GLFW!\n");
			exit(1);
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
		window = glfwCreateWindow(800, 600, "My Arkanoid", NULL, NULL);
		if (window == NULL) {
			fprintf(stderr, "Failed to create window!\n");
			exit(1);
		}

		glfwMakeContextCurrent(window);
		glfwSwapInterval(1); // Enable vsync

		if (!gladLoadGL(glfwGetProcAddress))
		{
			fprintf(stderr, "Failed to initialize OpenGL loader!\n");
			exit(1);
		}
	}

	void Io::initImGui()
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

#ifdef IO_USE_GAME_IMPLEMENTATION
	void Io::init(State* state)
	{
		this->state = state;
	}
#endif

	Io::~Io()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(window);
		glfwTerminate();
	}

	ImGuiIO& Io::getIo()
	{
		return *io;
	}

	bool Io::keyPressed(int key, bool once)
	{
		bool key_down = io->KeysDown[key];
		if (once)
			key_down &= key_down != oldKeysDown[key];
		return key_down;
	}

	void Io::drawText(ImDrawList& draw_list, char *text, Vect position, ImVec4 color, float size)
	{
		std::string textString(text);
		ImU32 textColor = ImGui::ColorConvertFloat4ToU32(color);
		draw_list.AddText(ImGui::GetIO().Fonts->Fonts[0], 32.0f, position, textColor, textString.c_str());
	}

	void Io::setContainerSize(Vect size)
	{
		container_size = size;
		updateCoordsToScreen();
	}

	void Io::updateCoordsToScreen()
	{
		coords_to_screen = Vect(io->DisplaySize.x / container_size.x, io->DisplaySize.y / container_size.y);
	}

	Vect Io::translateCoords(Vect point)
	{
		return point * coords_to_screen;
	}

	float Io::getElapsedTime()
	{
		return render_elapsed_time;
	}

	void Io::tick(RenderFunction render)
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// TODO: optimize, call when resize, if possible
		updateCoordsToScreen();

		double cur_time = glfwGetTime();
		render_elapsed_time = (float)(std::min(cur_time - last_time, 1.0));
		last_time = cur_time;

		ImDrawList* bg_drawlist = ImGui::GetBackgroundDrawList();
#ifdef IO_USE_GAME_IMPLEMENTATION
		render(*state, *bg_drawlist);
#else
		render(*bg_drawlist);
#endif

		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		updateKeys();
	}

	void Io::updateKeys()
	{
		memcpy(oldKeysDown, io->KeysDown, sizeof(oldKeysDown));
	}
}
