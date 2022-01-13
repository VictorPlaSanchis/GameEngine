#include "GameEngine.h"
#include "InputSystem/InputSystem.h"
#include "SceneSystem/SceneSystem.h"
#include <iostream>


#define DEBUG(x) std::cout << x << std::endl;

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

void GameEngine::InitializeGameEngine() 
{
	windowGame = glfwCreateWindow(640, 480, "Game Engine by Vitolo Paolo 12/01/2022 (R)", NULL, NULL);
	SceneSystem::get()->addScene();
	InputSystem::get()->addListener(this);
}

void GameEngine::update()
{

	InitializeGameEngine();

	while (!glfwWindowShouldClose(GameEngine::windowGame)) {

		InputSystem::get()->update();
		SceneSystem::get()->currentScene->UpdateScene();

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(GameEngine::windowGame);

		/* Poll for and process events */
		glfwWaitEventsTimeout(1.0);

	}

	glfwTerminate();

}
