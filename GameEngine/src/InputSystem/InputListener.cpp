#include "InputListener.h"
#include "../GameEngine.h"
#include <iostream>

void listenKeyboard(GLFWwindow* window, int keyCode, int scanCode, int action, int mods) 
{
	if(action == GLFW_PRESS)
		std::cout << char(keyCode) << std::endl;
}

void listenMouse(GLFWwindow* window, int keyCode, int action, int mods)
{
	std::cout << keyCode << std::endl;
	return;
}

InputListener::InputListener()
{
}

InputListener::~InputListener()
{
}

void InputListener::refresh()
{	
	glfwSetKeyCallback(GameEngine::get()->windowGame, listenKeyboard);
	glfwSetMouseButtonCallback(GameEngine::get()->windowGame, listenMouse);
}

