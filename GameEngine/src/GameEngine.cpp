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
#include "Debug/whiteSquare.h"
#include "Debug/blackSquare.h"
#include "Debug/ChessBoard.h"

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
		
		PROFILE_FUNCTION();
		{
			PROFILE_SCOPE("Initializing scene")

			Scene* scene1 = SceneManagementVGE.createScene();

			ChessBoard* chessBoard = new ChessBoard();
			chessBoard->transform->move(Vector3F(1.0f, 1.0f, 0.0f));

			scene1->addObject(chessBoard);

		}
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

			unsigned int frames = 0;
			double second = 1.0, acc = 0.0, lastAcc = 0.0;
			std::vector<unsigned int> framesPerSecond = std::vector<unsigned int>(0);

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
				
				frames++;
				acc += glfwGetTime() - lastAcc;
				lastAcc = glfwGetTime();

				if (acc > second) {
					framesPerSecond.push_back(frames);
					ConsoleWarningS("fps: " + std::to_string(frames), APPLICATION);
					frames = 0;
					acc = 0.0f;
				}
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
