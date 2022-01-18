#include "InputSystem.h"
#include "../GameEngine.h"
#include <GLFW/glfw3.h>
#include <iostream>

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

InputSystem* InputSystem::get()
{
	static InputSystem inputSystem;
	return &inputSystem;
}

bool InputSystem::isKeyPressed(int keyCode) 
{
	GLFWwindow* appWindow = GameEngine::get()->getWindowGame();
	int state = glfwGetKey(appWindow, keyCode);
	bool ret = state == GLFW_PRESS && lastKeyState[keyCode] == GLFW_RELEASE;
	lastKeyState[keyCode] = state;
	return ret;
}

bool InputSystem::isKeyDown(int keyCode)
{
	GLFWwindow* appWindow = GameEngine::get()->getWindowGame();
	int state = glfwGetKey(appWindow, keyCode);
	lastKeyState[keyCode] = state;
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool InputSystem::isKeyReleased(int keyCode)
{
	GLFWwindow* appWindow = GameEngine::get()->getWindowGame();
	int state = glfwGetKey(appWindow, keyCode);
	bool ret = state == GLFW_RELEASE && (lastKeyState[keyCode] == GLFW_PRESS || lastKeyState[keyCode] == GLFW_REPEAT);
	lastKeyState[keyCode] = state;
	return ret;
}
