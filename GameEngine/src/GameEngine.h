#pragma once
#include "InputSystem/InputSystem.h"
#include <GLFW/glfw3.h>

class GameEngine
{
private:

	GLFWwindow* windowGame;

public:

	GameEngine();
	~GameEngine();

	static GameEngine* get();
	GLFWwindow* getWindowGame();

	void Init();
	void Run();

};

