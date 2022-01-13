#pragma once
#include "InputSystem/InputListener.h"

class GameEngine : public InputListener
{

private:

public:

	GameEngine();
	~GameEngine();

	GLFWwindow* windowGame;

	static GameEngine* get();

	void InitializeGameEngine();
	void update();

};

