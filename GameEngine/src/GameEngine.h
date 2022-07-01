#pragma once
#include <GLFW/glfw3.h>
#include "InputSystem/InputSystem.h"

namespace vge {

	class GameEngine
	{
	private:

		GLFWwindow* windowGame;
		unsigned int width, heigth;

	public:

		GameEngine();
		~GameEngine();

		static GameEngine* get();
		GLFWwindow* getWindowGame();
		const char* getOpenGLversion();
		float getAspect() { return (float)this->width / (float)this->heigth; }
		unsigned int getWidth() { return this->width; }
		unsigned int getHeigth() { return this->heigth; }

		void Init();
		void Run();

	};

#define GameEngineVGE (*vge::GameEngine::get())

}