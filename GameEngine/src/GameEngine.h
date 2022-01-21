#pragma once
#include <GLFW/glfw3.h>
#include "InputSystem/InputSystem.h"

namespace vge {

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

}

