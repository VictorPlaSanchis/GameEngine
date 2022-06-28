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
#include "./ImGui/ImGuiController.h"

#include "./Debug/Instrumentor.h"

#include "./Debug/MyGameObject.h"
#include "./Object/Camera.h"

namespace vge {

	void GameEngine::Init()
	{
		// Initializing glfw and glew
		if (!glfwInit()) glfwTerminate();

		// Creating window context
		windowGame = glfwCreateWindow(1280, 720, "Game Engine by Vitolo Paolo 12/01/2022 (R)", NULL, NULL);
		glfwMakeContextCurrent(windowGame);

		// Needs window context
		std::string openGLversion = "";
		const char* openGLversionPtr = (const char*)glGetString(GL_VERSION);
		for (int i = 0; i < 3; i++) {
			openGLversion += *openGLversionPtr;
			openGLversionPtr++;
		}
		Console::debug("Running OpenGL version " + (std::string)getOpenGLversion() + ".", Console::YELLOW, Console::APPLICATION);

		// Initializing engines...
		InputSystem::get()->Init();
		GraphicsEngine::get()->Init();

		SceneManagement::get()->Ini();
		SceneManagement::get()->addScene();

		ImGuiController::get()->Init();

	}

	void InitializeDebugGame() {

		// Creating a game object for Debugging
		MyGameObject* object = new MyGameObject();
		Camera* cameraScene = new Camera();

		// Adding object into current scene of the game
		SceneManagement::get()->getCurrentScene()->addObject(object);
		SceneManagement::get()->getCurrentScene()->addObject(cameraScene);
		return;

	}

	void GameEngine::Run()
	{
		PROFILE_FUNCTION();
		{
			PROFILE_SCOPE("Executing GameEngine")
			glfwSetTime(0);
			Console::debug("Game Engine is running...", Console::COLOR::GREEN, Console::SENDER::APPLICATION);
			Console::debug("ImGui is initialized.", Console::COLOR::YELLOW, Console::SENDER::GUI);

			// --------------------------

			InitializeDebugGame();

			// --------------------------

			while (!glfwWindowShouldClose(GameEngine::windowGame)) 
			{
				PROFILE_SCOPE("FRAME TIME GameEngine")

				InputSystem::get()->Update();
				SceneManagement::get()->getCurrentScene()->UpdateScene();

				// clearing last screen frame
				glClear(GL_COLOR_BUFFER_BIT);
				GraphicsEngine::get()->DrawData();

				// ImGui
				ImGuiController::get()->Run();

				// Polling and swapping screen buffers
				glfwPollEvents();
				glfwSwapBuffers(GameEngine::windowGame);
			}

			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();

			glfwTerminate();

		}
	}

	const char* GameEngine::getOpenGLversion()
	{
		return (const char*)glGetString(GL_VERSION);
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
