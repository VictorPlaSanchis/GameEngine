#ifdef _WIN32
#include <Windows.h>	// avoid compilation redefinition of APIENTRY
#endif
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "GameEngine.h"
#include <string>
#include "InputSystem/InputSystem.h"
#include "SceneSystem/SceneManagement.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Shader.h"

#include "./ImGui/ImGuiController.h"

#include "./Debug/MyGameObject.h"
#include "./Object/Camera.h"
#include "Debug/Instrumentor.h"
#include <iostream>

namespace vge {

	void GameEngine::Init()
	{

		// Initializing glfw and glew
		if (!glfwInit()) glfwTerminate();

		// Creating window context
		this->width = 1280;
		this->heigth = 720;
		windowGame = glfwCreateWindow(this->width, this->heigth, "Game Engine by Vitolo Paolo 12/01/2022 (R)", NULL, NULL);
		glfwMakeContextCurrent(windowGame);

		// Needs window context
		std::string openGLversion = "";
		const char* openGLversionPtr = (const char*)glGetString(GL_VERSION);
		for (int i = 0; i < 3; i++) {
			openGLversion += *openGLversionPtr;
			openGLversionPtr++;
		}
		ConsoleWarning("Running OpenGL version " + (std::string)getOpenGLversion() + ".");

		// Initializing engines...
		InputSystemVGE.Init();
		GraphicsEngineVGE.Init();
		SceneManagementVGE.Ini();
		ImGuiControllerVGE.Init();

	}

	void InitializeDebugGame() {

		Scene* scene1 = SceneManagementVGE.createScene();
		Scene* scene2 = SceneManagementVGE.createScene();

		// Creating gameobjects for debugging
		MyGameObject* object = new MyGameObject();
		MyGameObject* object2 = new MyGameObject();
		object2->transform->move({1.0f, 0.0f, -1.0f});
		object->transform->move({-1.0f, 0.0f, -3.0f });

		// Adding object into scene 1 of the game
		scene1->addObject(object);
		scene1->addObject(object2);

		// Adding object into scene 2 of the game
		scene2->addObject(object2);
		scene2->getCameraScene()->transform->move({-2.0f, 4.0f, 1.0f});

	}

	void saveImage(char* filepath, GLFWwindow* w) {
		int width, height;
		glfwGetFramebufferSize(w, &width, &height);
		GLsizei nrChannels = 3;
		GLsizei stride = nrChannels * width;
		stride += (stride % 4) ? (4 - stride % 4) : 0;
		GLsizei bufferSize = stride * height;
		std::vector<char> buffer(bufferSize);
		glPixelStorei(GL_PACK_ALIGNMENT, 4);
		glReadBuffer(GL_FRONT);
		glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());
		//GameEngine::get()->preBuffer.push_back(buffer);
		//if (GameEngine::get()->preBuffer.size() > GameEngine::get()->sizePreBuffer) {
		//	for(std::vector<char> bufferX : GameEngine::get()->preBuffer)
				stbi_write_png(filepath, width, height, nrChannels, buffer.data(), stride);
		//	GameEngine::get()->preBuffer.clear();
		//}
		//stbi_flip_vertically_on_write(true);
	}

	std::string getNumber(int k, int maxNum) {
		std::string num = "";
		int i = 0;
		while (k > 0) {
			int a = k % 10;
			num =  std::to_string(a) + num;
			i++;
			k = k / 10;
		}
		std::string pre = "";
		for (int b = i; b < maxNum; b++) pre += "0";
		
		return pre + num;
	}

	void GameEngine::Run()
	{
		PROFILE_FUNCTION();
		{
			PROFILE_SCOPE("Executing GameEngine")
			glfwSetTime(0.0);
			ConsoleDebug("Game Engine is running...", GREEN);
			ConsoleWarningS("ImGui is initialized.", GUI);

			// --------------------------

			InitializeDebugGame();

			// --------------------------

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);

			unsigned int frames = 0;
			double second = 1.0, acc = 0.0, lastAcc = 0.0;
			std::vector<unsigned int> framesPerSecond = std::vector<unsigned int>(0);

			int i = 0, k = 0;
			while (!glfwWindowShouldClose(GameEngine::windowGame)) 
			{
				PROFILE_SCOPE("FRAME TIME GameEngine")
				InputSystemVGE.Update();
				GraphicsEngineVGE.CleanData();
				SceneManagementVGE.getCurrentScene()->UpdateScene();

				// clearing last screen frame
				glClearColor(0.0f, 0.1f, 0.2f, 0.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				GraphicsEngineVGE.DrawData();



				// ------------------------------

					std::string filepath = "./videoOutput/img" + getNumber(i,10) + ".png";
					saveImage(&filepath[0], this->getWindowGame());
					ConsoleLog("FRAME SAVED");
					

				// ------------------------------

				// ImGui
				ImGuiControllerVGE.Run();

				// Polling and swapping screen buffers
				glfwPollEvents();
				glfwSwapBuffers(GameEngine::windowGame);
				
				frames++;
				acc += glfwGetTime() - lastAcc;
				lastAcc = glfwGetTime();

				if (acc > second) {
					framesPerSecond.push_back(frames);
					ConsoleWarningS("fps: " + std::to_string(frames), APPLICATION);
					frames = 0;
					acc = 0.0f;
				}
				i++;
			}

			glDisable(GL_BLEND);
			glDisable(GL_DEPTH_TEST);

			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();

			glfwTerminate();

		}
	}

	const char* GameEngine::getOpenGLversion()
	{
		return (const char*)glGetString(GL_VERSION);
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
		return this->windowGame;
	}

}
