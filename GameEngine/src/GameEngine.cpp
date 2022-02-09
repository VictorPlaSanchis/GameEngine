#ifdef _WIN32
#include <Windows.h>	// avoid compilation redefinition of APIENTRY
#endif
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GameEngine.h"
#include <string>
#include "InputSystem/InputSystem.h"
#include "SceneSystem/SceneManagement.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Shader.h"
#include "Log/Console.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

namespace vge {

	void GameEngine::Init()
	{
		// Initializing glfw and glew
		if (!glfwInit()) glfwTerminate();

		// Creating window context
		windowGame = glfwCreateWindow(640, 420, "Game Engine by Vitolo Paolo 12/01/2022 (R)", NULL, NULL);
		glfwMakeContextCurrent(windowGame);

		// Needs window context
		std::string openGLversion = "";
		const char* openGLversionPtr = (const char*)glGetString(GL_VERSION);
		for (int i = 0; i < 3; i++) {
			openGLversion += *openGLversionPtr;
			openGLversionPtr++;
		}
		Console::debug("Running OpenGL version " + openGLversion + ".", Console::YELLOW, Console::APPLICATION);

		// Initializing engines...
		InputSystem::get()->Init();
		GraphicsEngine::get()->Init();

		SceneManagement::get()->addScene();

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(windowGame, true);
		ImGui_ImplOpenGL3_Init(std::stod(openGLversion));

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

	}

	void GameEngine::Run()
	{

		glfwSetTime(0);
		Console::debug("Game Engine is running...", Console::COLOR::GREEN, Console::SENDER::APPLICATION);



		Console::debug("ImGui is initialized.", Console::COLOR::YELLOW, Console::SENDER::GUI);

		while (!glfwWindowShouldClose(GameEngine::windowGame)) {

			// Updating game engines
			SceneManagement::get()->getCurrentScene()->UpdateScene();
			InputSystem::get()->Update();


			// clearing last screen frame
			glClear(GL_COLOR_BUFFER_BIT);

			// ImGui events
			// feed inputs to dear imgui, start new frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			// render your GUI
			ImGui::Begin("IM GUI EXAMPLE WINDOW");
			ImGui::Text("OpenGL running:");
			ImGui::Text((const char*)glGetString(GL_VERSION));
			ImGui::End();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


			// Polling and swapping screen buffers
			glfwPollEvents();
			glfwSwapBuffers(GameEngine::windowGame);
		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwTerminate();
		
	}

	GameEngine::GameEngine()
	{
	}

	GameEngine::~GameEngine()
	{
	}

	GameEngine* GameEngine::get()
	{
		static GameEngine gameEngine;
		return &gameEngine;
	}

	GLFWwindow* GameEngine::getWindowGame()
	{
		return GameEngine::get()->windowGame;
	}

}
