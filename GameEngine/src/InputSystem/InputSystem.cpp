#ifdef _WIN32
#include <Windows.h>	// avoid compilation redefinition of APIENTRY
#endif
#include "InputSystem.h"
#include "../GameEngine.h"

namespace vge {


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

	void InputSystem::Init()
	{
	}

	void InputSystem::Update()
	{
		memcpy(lastKeyState, keyState, sizeof(unsigned char) * 256);
		memcpy(lastMouseState, mouseState, sizeof(unsigned char) * 5);
	}

	bool InputSystem::isKeyPressed(int keyCode)
	{
		int state = glfwGetKey(GameEngine::get()->getWindowGame(), keyCode);
		bool ret = state == GLFW_PRESS && lastKeyState[keyCode] == GLFW_RELEASE;
		keyState[keyCode] = state;
		return ret;
	}

	bool InputSystem::isKeyDown(int keyCode)
	{
		int state = glfwGetKey(GameEngine::get()->getWindowGame(), keyCode);
		bool ret = state == GLFW_PRESS;
		keyState[keyCode] = state;
		return ret;
	}

	bool InputSystem::isKeyReleased(int keyCode)
	{
		int state = glfwGetKey(GameEngine::get()->getWindowGame(), keyCode);
		bool ret = state == GLFW_RELEASE && lastKeyState[keyCode] == GLFW_PRESS;
		keyState[keyCode] = state;
		return ret;
	}

	bool InputSystem::isMouseDown(int keyCode)
	{
		int state = glfwGetMouseButton(GameEngine::get()->getWindowGame(), keyCode);
		bool ret = state == GLFW_PRESS;
		mouseState[keyCode] = state;
		return ret;
	}

	bool InputSystem::isMousePressed(int keyCode)
	{
		int state = glfwGetMouseButton(GameEngine::get()->getWindowGame(), keyCode);
		bool ret = state == GLFW_PRESS && lastMouseState[keyCode] == GLFW_RELEASE;
		mouseState[keyCode] = state;
		return ret;
	}

	bool InputSystem::isMouseReleased(int keyCode)
	{
		int state = glfwGetMouseButton(GameEngine::get()->getWindowGame(), keyCode);
		bool ret = state == GLFW_RELEASE && lastMouseState[keyCode] == GLFW_PRESS;
		mouseState[keyCode] = state;
		return ret;
	}


	int InputSystem::getMousePosX()
	{
		double xPos;
		glfwGetCursorPos(GameEngine::get()->getWindowGame(), &xPos, nullptr);
		return (int)xPos;
	}

	int InputSystem::getMousePosY()
	{
		double yPos;
		glfwGetCursorPos(GameEngine::get()->getWindowGame(), nullptr, &yPos);
		return (int)yPos;
	}



}