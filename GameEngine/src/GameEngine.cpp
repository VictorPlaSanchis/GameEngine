#include "GameEngine.h"
#include "InputSystem/InputSystem.h"
#include "SceneSystem/SceneManagement.h"
#include "Log/Log.h"
// #########################################
#include "Object/Object.h"
#include "Object/ExampleComponent.h"
// #########################################

void GameEngine::Init()
{

	Log::get()->Init();
	InputSystem::get()->Init();

	DEBUG_APP_INFO("Logs initialized.");
	DEBUG_APP_WARNING("Game Engine initializing...");

	windowGame = glfwCreateWindow(640, 420, "Game Engine by Vitolo Paolo 12/01/2022 (R)", NULL, NULL);
	SceneManagement::get()->addScene();

	DEBUG_APP_INFO("Main Scene created.");

	DEBUG_ISL_WARNING("Input System initializing...");
	DEBUG_APP_INFO("Game Engine initialized.");
}

void GameEngine::Run()
{

	DEBUG_APP_INFO("Game Engine is now running.");

	// ##############################################################
	// TESTING SCENE ADDING SOME OBJECTS AND EXECUTING HIS BEHAVIOUR
	Object object = Object();
	object.addComponent(new ExampleComponent());
	SceneManagement::get()->getCurrentScene()->addObject(&object);
	// ##############################################################

	while (!glfwWindowShouldClose(GameEngine::windowGame)) {

		SceneManagement::get()->getCurrentScene()->UpdateScene();
		InputSystem::get()->Update();

		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(GameEngine::windowGame);
		glfwPollEvents();

	}

	glfwTerminate();
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