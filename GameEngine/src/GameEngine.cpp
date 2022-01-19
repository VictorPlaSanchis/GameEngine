#include "GameEngine.h"
#include "InputSystem/InputSystem.h"
#include "SceneSystem/SceneManagement.h"
#include <iostream>
#include "SourceScript.h"
#include "Log.h"

#define DEBUG(x) std::cout << x << std::endl;

void GameEngine::InitializeGameEngine()
{
	Log::Init();
	Log::debug(Log::getLogApp(), "Logs initialized.", spdlog::level::info);
	Log::debug(Log::getLogApp(), "Game Engine initializing...", spdlog::level::warn);

	windowGame = glfwCreateWindow(640, 420, "Game Engine by Vitolo Paolo 12/01/2022 (R)", NULL, NULL);
	SceneManagement::get()->addScene();

	Log::debug(Log::getLogApp(), "Main Scene created.", spdlog::level::info);

	const GLubyte* myGLVersion = glGetString(GL_VERSION);
	//Log::debug(Log::getLogApp(), myGLVersion, spdlog::level::warn);

	Log::debug(Log::getLogApp(), "Game Engine initialized.", spdlog::level::info);
}

GameEngine::GameEngine()
{
	if (!glfwInit()) glfwTerminate();
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

void GameEngine::update()
{

	InitializeGameEngine();

	SourceScript someScript = SourceScript();

	while (!glfwWindowShouldClose(GameEngine::windowGame)) {

		someScript.Update();
		SceneManagement::get()->getCurrentScene()->UpdateScene();

		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(GameEngine::windowGame);
		glfwPollEvents();

	}

	glfwTerminate();

}