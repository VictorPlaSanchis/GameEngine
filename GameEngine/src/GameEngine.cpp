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

#include "./ImGui/ImGuiController.h"

#include "./Debug/MyGameObject.h"
#include "./Object/Camera.h"
#include "Debug/Instrumentor.h"

namespace vge {

	void GameEngine::Init()
	{

		// Initializing glfw and glew
		if (!glfwInit()) glfwTerminate();

		// Creating window context
		this->width = 1280;
		this->heigth = 720;
		windowGame = glfwCreateWindow(this->width, this->heigth, "Game Engine by Vitolo Paolo 12/01/2022 (R)", NULL, NULL);
		glfwMakeContextCurrent(windowGame);

		// Needs window context
		std::string openGLversion = "";
		const char* openGLversionPtr = (const char*)glGetString(GL_VERSION);
		for (int i = 0; i < 3; i++) {
			openGLversion += *openGLversionPtr;
			openGLversionPtr++;
		}
		ConsoleWarning("Running OpenGL version " + (std::string)getOpenGLversion() + ".");

		// Initializing engines...
		InputSystemVGE.Init();
		GraphicsEngineVGE.Init();
		SceneManagementVGE.Ini();
		ImGuiControllerVGE.Init();

	}

	void InitializeDebugGame() {

		Scene* scene1 = SceneManagementVGE.createScene();
		Scene* scene2 = SceneManagementVGE.createScene();

		// Creating a game object for Debugging
		MyGameObject* object = new MyGameObject();
		MyGameObject* object2 = new MyGameObject();
		object2->transform->move({1.0f, 0.0f, -1.0f});
		object->transform->move({-1.0f, 0.0f, -3.0f });
		Camera* cameraScene = new Camera();
		Camera* cameraScene2 = new Camera();

		// Adding object into current scene of the game
		scene1->addObject(object);
		scene1->addObject(object2);
		scene1->addObject(cameraScene);

		// Adding object into current scene of the game
		scene2->addObject(object2);
		scene2->addObject(cameraScene2);

		return;

	}

	void GameEngine::Run()
	{
		PROFILE_FUNCTION();
		{
			PROFILE_SCOPE("Executing GameEngine")
			glfwSetTime(0.0);
			ConsoleDebug("Game Engine is running...", GREEN);
			ConsoleWarningS("ImGui is initialized.", GUI);

			// --------------------------

			InitializeDebugGame();

			// --------------------------

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);

			while (!glfwWindowShouldClose(GameEngine::windowGame)) 
			{
				PROFILE_SCOPE("FRAME TIME GameEngine")
				InputSystemVGE.Update();
				GraphicsEngineVGE.CleanData();
				SceneManagementVGE.getCurrentScene()->UpdateScene();

				// clearing last screen frame
				glClearColor(0.0f, 0.1f, 0.2f, 0.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				GraphicsEngineVGE.DrawData();
				// ImGui
				ImGuiControllerVGE.Run();

				// Polling and swapping screen buffers
				glfwPollEvents();
				glfwSwapBuffers(GameEngine::windowGame);
			}

			glDisable(GL_BLEND);
			glDisable(GL_DEPTH_TEST);

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
		return this->windowGame;
	}

}
