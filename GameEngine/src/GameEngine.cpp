#ifdef _WIN32
#include <Windows.h>	// avoid compilation redefinition of APIENTRY
#endif
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GameEngine.h"
#include "InputSystem/InputSystem.h"
#include "SceneSystem/SceneManagement.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Shader.h"
#include "Log/Console.h"

namespace vge {

	void GameEngine::Init()
	{
		// Initializing glfw and glew
		if (!glfwInit()) glfwTerminate();

		// Creating window context
		windowGame = glfwCreateWindow(640, 420, "Game Engine by Vitolo Paolo 12/01/2022 (R)", NULL, NULL);
		glfwMakeContextCurrent(windowGame);

		// Needs window context
		std::string versionGL = (const char*)glGetString(GL_VERSION);

		// Initializing engines...
		InputSystem::get()->Init();
		GraphicsEngine::get()->Init();

		SceneManagement::get()->addScene();

	}

	void GameEngine::Run()
	{
		glfwSetTime(0);

		// ##########################################

		float points[] = {
		   0.0f,  0.5f,  0.0f,
		   0.5f, -0.5f,  0.0f,
		  -0.5f, -0.5f,  0.0f
		};

		GLuint vbo = 0;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

		GLuint vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		// ##########################################

		int index = Console::COLOR(0);

		while (!glfwWindowShouldClose(GameEngine::windowGame)) {

			/*
			EXAMPLE OF PASSING UNIFORM DATA TO A SHADER
			
			int transformLocation = glGetUniformLocation(GraphicsEngine::get()->programID(), "transform");
			float transform[3];
			for (int i = 0; i < 3; i++) {
				transform[i] = (float)triangle.transform->getValues().get(i);
			}
			glProgramUniform3fv(GraphicsEngine::get()->programID(), transformLocation, 1, transform);*/

			Console::debug("GAME ENGINE is running...", Console::COLOR(index % 7), Console::APPLICATION);
			index++;

			SceneManagement::get()->getCurrentScene()->UpdateScene();
			InputSystem::get()->Update();

			glClear(GL_COLOR_BUFFER_BIT);

			GraphicsEngine::get()->Bind();
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glfwPollEvents();
			glfwSwapBuffers(GameEngine::windowGame);
		}

		glfwTerminate();
		
	}

	GameEngine::GameEngine()
	{
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

}
