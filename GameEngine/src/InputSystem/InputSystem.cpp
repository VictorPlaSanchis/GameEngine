#include <GLFW/glfw3.h>
#include "InputSystem.h"
#include "../GameEngine.h"
#include "../Log.h"

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
	std::string mssg = glfwGetKeyName(keyCode, GLFW_MOD_SHIFT);
	mssg += " Pressed.";
	if(ret) Log::debug(Log::getLogInputSystem(), mssg, spdlog::level::info);
	return ret;
}

bool InputSystem::isKeyDown(int keyCode)
{
	GLFWwindow* appWindow = GameEngine::get()->getWindowGame();
	int state = glfwGetKey(appWindow, keyCode);
	bool ret = state == GLFW_PRESS || state == GLFW_REPEAT;
	if (ret) {
		std::string mssg = glfwGetKeyName(keyCode, GLFW_MOD_SHIFT);
		mssg += " Down.";
		Log::debug(Log::getLogInputSystem(), mssg, spdlog::level::info);
	}
	lastKeyState[keyCode] = state;
	return ret;
}

bool InputSystem::isKeyReleased(int keyCode)
{
	GLFWwindow* appWindow = GameEngine::get()->getWindowGame();
	int state = glfwGetKey(appWindow, keyCode);
	bool ret = state == GLFW_RELEASE && (lastKeyState[keyCode] == GLFW_PRESS || lastKeyState[keyCode] == GLFW_REPEAT);
	lastKeyState[keyCode] = state;
	std::string mssg = glfwGetKeyName(keyCode, GLFW_MOD_SHIFT);
	mssg += " Released.";
	if (ret) Log::debug(Log::getLogInputSystem(), mssg, spdlog::level::info);
	return ret;
}
